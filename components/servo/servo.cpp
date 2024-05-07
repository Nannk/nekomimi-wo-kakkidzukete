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

struct Parameters {
  int angle;
  uint8_t channel;
};

// someones SG90 works on 500µs ~ 2650µs (spec: 500µ ~ 2400µ)
uint16_t calc_duty_from_angle(int angle) {
  return (0.025 + (0.1325 - 0.025) * (double)angle / 180) * UINT16_MAX;
}

/* Initialises the servos. Returns channel number.
 * Should automatically distribute channels between servos.
 * Returns -1 if a servo could not be Initialised.
 *  @param pins[] - array of used pins that servos are on
 */
int Servo::servo_init(const uint8_t *pin) {
  int free_channel = 0;
  if (this->channels[7] != -1) {
    printf("max 8 channels are allowed");
    return -1;
  } else {
    for (int i = 0; i < sizeof(this->channels); i++) {
      if (this->channels[i] == -1)
        free_channel = i;
    }
    this->channels[free_channel] = free_channel;
    pwm_init(1000, (uint32_t *)50, free_channel, (uint32_t *)pin);
    return free_channel;
  }
}

void rotate_task(void *input_data) {
  Parameters *data{reinterpret_cast<Parameters *>(input_data)};
  pwm_set_duty(data->channel, calc_duty_from_angle(data->angle));
  pwm_start();
  vTaskDelay(20 / portTICK_PERIOD_MS);
  vTaskDelete(NULL);
}

void Servo::servo_rotate_to_angle(int angle, int channel) {
  Parameters *data = new Parameters;
  data->angle = angle;
  data->channel = channel;
  xTaskCreate(rotate_task, "rotate_task", 256, data, 1, NULL);
}
