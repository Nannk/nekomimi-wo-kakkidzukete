/**
Copied and modified code from Achim Pieters | StudioPieters®
 **/

#include "servo.h"
#include "esp_log.h"
#include <array>
#include <cstdint>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <pwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <uart.h>

static const char *TAG = "servo";

// servos use 500µs ~ 2500µs
uint16_t calc_duty_from_angle(int angle) {
  // return (0.025 + (0.1325 - 0.025) * (double)angle / 180) * UINT8_MAX;
  return ((2000 * (double)angle) / 180) + 500;
}

// initialise pwm
void Servo::servo_init() {
  ESP_LOGI(TAG, "initialising servos"); // debug
  pwm_init(5000, duties, 6, pins);
  pwm_set_phases(phases);
}

// function to run as a task
void rotate_task(void *input_data) {
  ESP_LOGD(TAG, "in create task");
  std::array<Parameters, 6> *data{
      reinterpret_cast<std::array<Parameters, 6> *>(input_data)};
  for (Parameters param : *data) {
    ESP_LOGD(TAG, "channel: %d angle: %d", param.channel, param.angle);
    pwm_set_duty(param.channel, param.angle);
  }
  pwm_start();
  // vTaskDelay(20 / portTICK_PERIOD_MS);
  //  pwm_stop(0x00);
  vTaskDelete(NULL);
}

// setter and task creator
void Servo::servo_rotate_to_angle(std::array<int, 6> &data) {

  for (int i = 0; i < 6; i++) {

    int *tmp = &data[i];
    persistent_params[i].angle = calc_duty_from_angle(*tmp);
    persistent_params[i].channel = i;
    ESP_LOGD(TAG, "in rotate to angle loop interation %d, data: %d", i,
             persistent_params[i].angle);
  }
  xTaskCreate(rotate_task, "rotate_task", 1024, &persistent_params, 5, NULL);
}
