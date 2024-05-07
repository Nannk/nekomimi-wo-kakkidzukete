
#include "ear.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "portmacro.h"
#include "poses.h"
#include <stdio.h>

#include "config.h"
#include "uart.h"

struct Ears {
  Ear leftear;
  Ear rightear;
};

bool toggle = true;

Ears ears;

void pose_looping(void *params) {
  Ears *ears{reinterpret_cast<Ears *>(params)};
  if (toggle) {
    choose_pose(20, ears->leftear, ears->rightear);
  } else {
    choose_pose(31, ears->leftear, ears->rightear);
  }
  ears->leftear.move_to_set_angles();
  ears->rightear.move_to_set_angles();
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

extern "C" void app_main() {
  uart_set_baudrate(UART_NUM_0, 112500);
  printf("setting up\n");
  printf("...\n");

  // vTaskDelay(1000 / portTICK_PERIOD_MS);
  ears.leftear.earsetup(LLEFTWINGPIN, LMAINPIN, LRIGHTWINGPIN);
  ears.rightear.earsetup(RLEFTWINGPIN, RMAINPIN, RRIGHTWINGPIN);

  choose_pose(31, ears.leftear, ears.rightear);
  ears.leftear.move_to_set_angles();
  ears.rightear.move_to_set_angles();

  printf("moved to default pose");

  Ears *ears_ptr = new Ears;
  ears_ptr->leftear = ears.leftear;
  ears_ptr->rightear = ears.rightear;
  xTaskCreate(pose_looping, "loop though poses", 256, ears_ptr, 2, NULL);

  fflush(stdout);
}
