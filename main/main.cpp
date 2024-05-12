
#include "ears.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_task_wdt.h"
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <gpio.h>
#include <stdio.h>
#include <uart.h>

static const char *TAG = "Main";

bool toggle = true;

static Ears ears;

void pose_looping(/*Ears &ears*/) {
  // Ears *ears{reinterpret_cast<Ears *>(prt_ears)};
  if (toggle) {
    ears.choose_pose(20);
  } else {
    ears.choose_pose(31);
  }
  toggle = !toggle;

  ESP_LOGD(TAG, "memory: %d", (int)heap_caps_get_free_size(MALLOC_CAP_32BIT));
  ears.move_to_set_angles();
  vTaskDelay(1000 / portTICK_RATE_MS);
}

extern "C" void app_main() {

  uart_set_baudrate(UART_NUM_0, 112500);
  ESP_LOGI(TAG, "setting up");

  // assign channels and start servos
  ears.ears_init({0, 1, 2, 3, 4, 5});

  ESP_LOGI(TAG, "done setting up");
  // ears.choose_pose(21);
  // ears.move_to_set_angles();
  // vTaskDelay(100 / portTICK_RATE_MS); // for assembling wing correctly
  while (true) {
    pose_looping();
    // xTaskCreate(pose_looping, "loop though poses", 4096, NULL, 1, NULL);
  }
  fflush(stdout);
}
