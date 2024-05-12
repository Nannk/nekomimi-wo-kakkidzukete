#include "ears.h"
#include "esp_log.h"
#include "servo.h"
#include <array>
#include <cstdio>
#include <sys/types.h>

static const char *TAG = "Ears";

void Ears::ears_init(std::array<int, 6> set_channels) {
  for (int i = 0; i < 6; i++) {
    channels[i] = set_channels[i];
    ESP_LOGD(TAG, "setting channel: %d", channels[i]);
  }
  servos.servo_init();
}

void Ears::set_ears_position(int left_angle_left, int left_angle_main,
                             int left_angle_right, int right_angle_left,
                             int right_angle_main, int right_angle_right) {
  angles[0] = left_angle_left;
  angles[1] = left_angle_main;
  angles[2] = left_angle_right;
  angles[3] = right_angle_left;
  angles[4] = right_angle_main;
  angles[5] = right_angle_right;
}

void Ears::move_to_set_angles() {
  ESP_LOGD(TAG, "in move to set angles");
  servos.servo_rotate_to_angle(angles);
}

void Ears::choose_pose(int poseNumber) {

  ESP_LOGD(TAG, "in choose pose %d", poseNumber);
  switch (poseNumber) {
  case 10:
    set_ears_position(106, 30, 26, /**/ 106, 150, 26);
    break;

  case 12:
    set_ears_position(53, 30, 79, /**/ 53, 150, 79);
    break;

  case 13:
    set_ears_position(132, 30, 132, /**/ 0, 150, 0);
    break;

  case 14:
    set_ears_position(0, 30, 0, 132, /**/ 150, 132);
    break;

  case 20:
    set_ears_position(106, 90, 26, /**/ 106, 90, 26);
    break;

  case 21:
    set_ears_position(0, 90, 132, /**/ 0, 90, 132);
    break;

  case 22:
    set_ears_position(53, 90, 79, /**/ 53, 90, 79);
    break;

  case 23:
    set_ears_position(132, 90, 132, /**/ 0, 90, 0);
    break;

  case 24:
    set_ears_position(0, 90, 0, /**/ 132, 90, 132);
    break;

  case 31:
    set_ears_position(0, 180, 132, /**/ 0, 0, 132);
    break;

  case 33:
    set_ears_position(0, 180, 0, /**/ 132, 0, 132);
    break;

  case 34:
    set_ears_position(132, 180, 132, /**/ 0, 0, 0);
    break;

  default:
    set_ears_position(0, 180, 132, /**/ 0, 0, 132);
    break;
  }
}
