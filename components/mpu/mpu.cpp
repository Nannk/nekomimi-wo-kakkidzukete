/* yank the I2C example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "mpu.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#include "esp_err.h"
#include "esp_log.h"

#include "driver/i2c.h"
#include "gpio.h"

static const char *TAG = "mpu";

/**
 * TEST CODE BRIEF
 *
 * This example will show you how to use I2C module by running two tasks on i2c
 * bus:
 *
 * - read external i2c sensor, here we use a MPU9250 sensor for instance.
 * - Use one I2C port(master mode) to read or write the other I2C port(slave
 * mode) on one ESP8266 chip.
 *
 * Pin assignment:
 *
 * - master:
 *    GPIO4 is assigned as the data signal of i2c master port
 *    GPIO5 is assigned as the clock signal of i2c master port
 */
/**
 * @brief i2c master initialization
 */

esp_err_t esp_init() {
  i2c_config_t conf;
  conf.mode = I2C_MODE_MASTER;
  conf.sda_io_num = (gpio_num_t)I2C_MASTER_SDA_IO;
  gpio_set_pull_mode((gpio_num_t)I2C_MASTER_SDA_IO, GPIO_PULLUP_ONLY);
  // conf.sda_pullup_en = (gpio_pullup_t)1;
  conf.scl_io_num = (gpio_num_t)I2C_MASTER_SCL_IO;
  gpio_set_pull_mode((gpio_num_t)I2C_MASTER_SCL_IO, GPIO_PULLUP_ONLY);
  // conf.scl_pullup_en = (gpio_pullup_t)1;
  conf.clk_stretch_tick =
      300; // 300 ticks, Clock stretch is about 210us, you can make changes
           // according to the actual situation.
  ESP_ERROR_CHECK(i2c_driver_install(I2C_MASTER_NUM, conf.mode));
  ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &conf));
  return ESP_OK;
}

/**
 * @brief test code to write mpu9250
 *
 * 1. send data
 * ___________________________________________________________________________________________________
 * | start | slave_addr + wr_bit + ack | write reg_address + ack | write
 * data_len byte + ack  | stop |
 * --------|---------------------------|-------------------------|----------------------------|------|
 *
 * @param i2c_num I2C port number
 * @param reg_address slave reg address
 * @param data data to send
 * @param data_len data length
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 *     - ESP_FAIL Sending command error, slave doesn't ACK the transfer.
 *     - ESP_ERR_INVALID_STATE I2C driver not installed or not in master mode.
 *     - ESP_ERR_TIMEOUT Operation timeout because the bus is busy.
 */
esp_err_t Mpu::mpu9250_write(i2c_port_t i2c_num, uint8_t reg_address,
                             uint8_t *data, size_t data_len) {
  int ret;
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, MPU9250_SENSOR_ADDR << 1 | WRITE_BIT,
                        ACK_CHECK_EN);
  i2c_master_write_byte(cmd, reg_address, ACK_CHECK_EN);
  i2c_master_write(cmd, data, data_len, ACK_CHECK_EN);
  i2c_master_stop(cmd);
  ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);

  return ret;
}

/**
 * @brief test code to read mpu9250
 *
 * 1. send reg address
 * ______________________________________________________________________
 * | start | slave_addr + wr_bit + ack | write reg_address + ack | stop |
 * --------|---------------------------|-------------------------|------|
 *
 * 2. read data
 * ___________________________________________________________________________________
 * | start | slave_addr + wr_bit + ack | read data_len byte + ack(last nack)  |
 * stop |
 * --------|---------------------------|--------------------------------------|------|
 *
 * @param i2c_num I2C port number
 * @param reg_address slave reg address
 * @param data data to read
 * @param data_len data length
 *
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG Parameter error
 *     - ESP_FAIL Sending command error, slave doesn't ACK the transfer.
 *     - ESP_ERR_INVALID_STATE I2C driver not installed or not in master mode.
 *     - ESP_ERR_TIMEOUT Operation timeout because the bus is busy.
 */
esp_err_t Mpu::mpu9250_read(i2c_port_t i2c_num, uint8_t reg_address,
                            uint8_t *data, size_t data_len) {
  int ret;
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, MPU9250_SENSOR_ADDR << 1 | WRITE_BIT,
                        ACK_CHECK_EN);
  i2c_master_write_byte(cmd, reg_address, ACK_CHECK_EN);
  i2c_master_stop(cmd);
  ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);

  if (ret != ESP_OK) {
    return ret;
  }

  cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, MPU9250_SENSOR_ADDR << 1 | READ_BIT, ACK_CHECK_EN);
  i2c_master_read(cmd, data, data_len, (i2c_ack_type_t)LAST_NACK_VAL);
  i2c_master_stop(cmd);
  ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);

  return ret;
}

// TODO: rewrite for 9250
esp_err_t Mpu::mpu9250_init(i2c_port_t i2c_num) {
  uint8_t cmd_data;
  vTaskDelay(100 / portTICK_RATE_MS);
  esp_init();
  cmd_data = 0x00; // reset mpu9250
  ESP_ERROR_CHECK(mpu9250_write(i2c_num, PWR_MGMT_1, &cmd_data, 1));
  cmd_data = 0x07; // Set the SMPRT_DIV
  ESP_ERROR_CHECK(mpu9250_write(i2c_num, SMPLRT_DIV, &cmd_data, 1));
  cmd_data = 0x06; // Set the Low Pass Filter
  ESP_ERROR_CHECK(mpu9250_write(i2c_num, CONFIG, &cmd_data, 1));
  cmd_data = 0x18; // Set the GYRO range
  ESP_ERROR_CHECK(mpu9250_write(i2c_num, GYRO_CONFIG, &cmd_data, 1));
  cmd_data = 0x01; // Set the ACCEL range
  ESP_ERROR_CHECK(mpu9250_write(i2c_num, ACCEL_CONFIG, &cmd_data, 1));
  return ESP_OK;
}

/*
static void i2c_task(void *arg) {
  uint8_t sensor_data[14];
  uint8_t who_am_i, i;
  double Temp;
  static uint32_t error_count = 0;
  int ret;

  mpu9250_init(I2C_MASTER_NUM);

  while (1) {
    who_am_i = 0;
    mpu9250_read(I2C_MASTER_NUM, WHO_AM_I, &who_am_i, 1);

    if (0x68 != who_am_i) {
      error_count++;
    }

    memset(sensor_data, 0, 14);
    ret = mpu9250_read(I2C_MASTER_NUM, ACCEL_XOUT_H, sensor_data, 14);

    if (ret == ESP_OK) {
      ESP_LOGI(TAG, "*******************\n");
      ESP_LOGI(TAG, "WHO_AM_I: 0x%02x\n", who_am_i);
      Temp = 36.53 +
             ((double)(int16_t)((sensor_data[6] << 8) | sensor_data[7]) / 340);
      ESP_LOGI(TAG, "TEMP: %d.%d\n", (uint16_t)Temp,
               (uint16_t)(Temp * 100) % 100);

      for (i = 0; i < 7; i++) {
        ESP_LOGI(TAG, "sensor_data[%d]: %d\n", i,
                 (int16_t)((sensor_data[i * 2] << 8) | sensor_data[i * 2 + 1]));
      }

      ESP_LOGI(TAG, "error_count: %d\n", error_count);
    } else {
      ESP_LOGE(TAG, "No ack, sensor not connected...skip...\n");
    }

    vTaskDelay(100 / portTICK_RATE_MS);
  }

  i2c_driver_delete(I2C_MASTER_NUM);
}

*/
