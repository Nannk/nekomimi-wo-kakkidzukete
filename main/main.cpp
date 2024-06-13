
#include "config.h"
#include "ears.h"
#include "mpu.h"
#include <cstdint>
#include <esp_heap_caps.h>
#include <esp_log.h>
#include <esp_spi_flash.h>
#include <esp_task_wdt.h>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <gpio.h>
#include <stdio.h>
#include <uart.h>

static const char *TAG = "Main";

static Ears ears;
static Mpu mpu;
// mpu variables
uint8_t sensor_data[14];
uint8_t who_am_i, i;
double Temp;
int ret;
long long current_millis;
long long previous_millis;

void mpu_task(void *Parameters) {

  uart_set_baudrate(UART_NUM_0, 112500);

  // assign channels and start servos
  ears.ears_init({0, 1, 2, 3, 4, 5});
  // initialise i2c and mpu
  mpu.mpu9250_init(I2C_MASTER_NUM);

  ESP_LOGI(TAG, "done setting up");
  // ears.choose_pose(21);
  // ears.move_to_set_angles();
  // vTaskDelay(1000 / portTICK_RATE_MS); // for assembling wing correctly

  // test thing
  ears.choose_pose(31);
  ears.move_to_set_angles();
  previous_millis = esp_timer_get_time() / 1000;

  while (1) {

    // mpu.mpu9250_read(I2C_MASTER_NUM, WHO_AM_I, &who_am_i, 1);

    // memset(sensor_data, 0, 14);
    ret = mpu.mpu9250_read(I2C_MASTER_NUM, ACCEL_XOUT_H, sensor_data, 14);

    if (ret == ESP_OK) {
      // ESP_LOGI(TAG, "*******************");

      // for (i = 0; i < 14; i++) {
      ESP_LOGI(TAG, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
               (int16_t)(sensor_data[0]), (int16_t)(sensor_data[1]),
               (int16_t)(sensor_data[2]), (int16_t)(sensor_data[3]),
               (int16_t)(sensor_data[4]), (int16_t)(sensor_data[5]),
               (int16_t)(sensor_data[6]), (int16_t)(sensor_data[7]),
               (int16_t)(sensor_data[8]), (int16_t)(sensor_data[9]),
               (int16_t)(sensor_data[10]), (int16_t)(sensor_data[11]),
               (int16_t)(sensor_data[12]), (int16_t)(sensor_data[13]));
      //}

      // ESP_LOGI(TAG, "error_count: %d\n", error_count);
    } else {
      ESP_LOGE(TAG, "No ack, sensor not connected...skip...\n");
    }

    // ESP_LOGD(TAG, "memory: %d",
    // (int)heap_caps_get_free_size(MALLOC_CAP_32BIT));

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
  i2c_driver_delete(I2C_MASTER_NUM);
  fflush(stdout);
}

extern "C" void app_main() {
  xTaskCreate(mpu_task, "mpu_task", 2048, NULL, 10, NULL);
}
