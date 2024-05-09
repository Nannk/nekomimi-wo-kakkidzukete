
#include "ear.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "portmacro.h"
#include "poses.h"
#include "servo.h"
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <gpio.h>
#include <stdio.h>
#include <uart.h>

struct Ears {
  Servo servos;
  Ear leftear;
  Ear rightear;
};

bool toggle = true;

static Ears ears;

void pose_looping(Ears &ears) {
  if (toggle) {
    choose_pose(20, ears.leftear, ears.rightear);
  } else {
    choose_pose(31, ears.leftear, ears.rightear);
  }
  toggle = !toggle;

  printf("mem: %d\n", (int)heap_caps_get_free_size(MALLOC_CAP_32BIT));
  ears.leftear.print_angles_debug();  // debug
  ears.rightear.print_angles_debug(); // debug
  printf("---\n");
  ears.leftear.move_to_set_angles(ears.servos);
  ears.rightear.move_to_set_angles(ears.servos);
  vTaskDelay(50 / portTICK_RATE_MS);
}

extern "C" void app_main() {
  uart_set_baudrate(UART_NUM_0, 112500);
  printf("setting up\n"); // debug

  // assign channels
  ears.leftear.ear_init(0, 1, 2);
  ears.rightear.ear_init(3, 4, 5);
  // start servos
  ears.servos.servo_init();

  //  vTaskDelay(1000 / portTICK_PERIOD_MS);
  // ears.leftear.earsetup(ears.servos, &lleftpin, &lmainpin, &lrightpin);
  // ears.rightear.earsetup(ears.servos, &rleftpin, &rmainpin, &rrightpin);

  choose_pose(31, ears.leftear, ears.rightear);
  ears.leftear.move_to_set_angles(ears.servos);
  ears.rightear.move_to_set_angles(ears.servos);
  while (true) {
    pose_looping(ears);
    // xTaskCreate(pose_looping, "loop though poses", 4096, ears, 2, NULL);
  }
  fflush(stdout);
}
