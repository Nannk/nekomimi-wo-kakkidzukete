
#include "config.h"
#include "ears.h"
#include "mpu.h"
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
static uint32_t error_count = 0;
int ret;
long long current_millis;

void setup() {

  uart_set_baudrate(UART_NUM_0, 112500);

  // assign channels and start servos
  ears.ears_init({0, 1, 2, 3, 4, 5});
  // initialise i2c and mpu
  mpu.mpu9250_init(I2C_MASTER_NUM);

  ESP_LOGI(TAG, "done setting up");
  // ears.choose_pose(21);
  // ears.move_to_set_angles();
  // vTaskDelay(100 / portTICK_RATE_MS); // for assembling wing correctly

  // test thing
  ears.choose_pose(31);
  ears.move_to_set_angles();
  current_millis = esp_timer_get_time();
}

extern "C" void app_main() {

  setup();

  while (1) {

    if (esp_timer_get_time() - current_millis >= 10) {
      // mpu.mpu9250_read(I2C_MASTER_NUM, WHO_AM_I, &who_am_i, 1);

      // memset(sensor_data, 0, 14);
      ret = mpu.mpu9250_read(I2C_MASTER_NUM, ACCEL_XOUT_H, sensor_data, 14);

      if (ret == ESP_OK) {
        ESP_LOGI(TAG, "*******************");

        for (i = 0; i < 14; i++) {
          ESP_LOGI(TAG, "%d: %d ", i, (int16_t)(sensor_data[i]));
        }

        // ESP_LOGI(TAG, "error_count: %d\n", error_count);
      } else {
        ESP_LOGE(TAG, "No ack, sensor not connected...skip...\n");
      }

      // ESP_LOGD(TAG, "memory: %d",
      // (int)heap_caps_get_free_size(MALLOC_CAP_32BIT));
    } else {
      vTaskDelay(1 / portTICK_RATE_MS);
    }
  }
  // xTaskCreate(pose_looping, "loop though poses", 4096, NULL, 1, NULL);
  i2c_driver_delete(I2C_MASTER_NUM);
  fflush(stdout);
}
