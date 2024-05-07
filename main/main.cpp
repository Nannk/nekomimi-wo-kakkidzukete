
#include "ear.h"
#include "esp_spi_flash.h"
#include "portmacro.h"
#include "poses.h"
#include "servo.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <gpio.h>
#include <stdio.h>
#include <uart.h>

uint32_t pins[6] = {14, 0, 12, 13, 2, 15};

struct Ears {
  Servo servos;
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
  toggle = !toggle;
  ears->leftear.move_to_set_angles(ears->servos);
  ears->rightear.move_to_set_angles(ears->servos);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

extern "C" void app_main() {
  uart_set_baudrate(UART_NUM_0, 112500);
  printf("setting up\n");
  printf("...\n");

  // assign channels
  ears.leftear.ear_init(0, 1, 2);
  ears.rightear.ear_init(3, 4, 5);
  // start servos
  ears.servos.servo_init(pins);

  printf("done configuring servos\n");

  vTaskDelay(1000 / portTICK_PERIOD_MS);
  // ears.leftear.earsetup(ears.servos, &lleftpin, &lmainpin, &lrightpin);
  // ears.rightear.earsetup(ears.servos, &rleftpin, &rmainpin, &rrightpin);

  choose_pose(31, ears.leftear, ears.rightear);
  ears.leftear.move_to_set_angles(ears.servos);
  ears.rightear.move_to_set_angles(ears.servos);

  printf("moved to default pose");

  Ears *ears_ptr = new Ears;
  ears_ptr->leftear = ears.leftear;
  ears_ptr->rightear = ears.rightear;
  xTaskCreate(pose_looping, "loop though poses", 256, ears_ptr, 2, NULL);

  fflush(stdout);
}
