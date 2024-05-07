/**

   Copyright 2022 Achim Pieters | StudioPieters®

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 **/

#include "servo.h"
#include "config.h"
#include <cstdint>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <pwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <uart.h>

uint32_t duties[6] = {500, 500, 500, 500, 500, 500};

struct Parameters {
  int angle;
  uint8_t channel;
};

uint32_t default_duty = (0.025 + (0.1325 - 0.025) / 2) * UINT16_MAX;

// someones SG90 works on 500µs ~ 2650µs (spec: 500µ ~ 2400µ)
uint16_t calc_duty_from_angle(int angle) {
  return (0.025 + (0.1325 - 0.025) * (double)angle / 180) * UINT16_MAX;
}

/* Initialises the servos. Returns channel number.
 * Should automatically distribute channels between servos.
 * Returns -1 if a servo could not be Initialised.
 *  @param pins[] - array of used pins that servos are on
 */
void Servo::servo_init(uint32_t pin[]) {
  printf("initialising servos\n");
  pwm_init(2000, duties, 6, pin); // here somewher "LoadProhibite" exception
  printf("servos done");
}

void rotate_task(void *input_data) {
  Parameters *data{reinterpret_cast<Parameters *>(input_data)};
  pwm_set_duty(data->channel, calc_duty_from_angle(data->angle));
  pwm_start();

  printf("rotated channel %d", data->channel);

  vTaskDelay(20 / portTICK_PERIOD_MS);
  vTaskDelete(NULL);
}

void Servo::servo_rotate_to_angle(int angle, int channel) {
  Parameters *data = new Parameters;
  data->angle = angle;
  data->channel = channel;
  xTaskCreate(rotate_task, "rotate_task", 2048, data, 1, NULL);
}
