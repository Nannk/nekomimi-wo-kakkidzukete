#ifndef Ears_h
#define Ears_h

#include "servo.h"
#include <array>
#include <sys/types.h>

class Ears {
public:
  void ears_init(std::array<int, 6> set_channels);
  void set_ears_position(int left_angle_left, int left_angle_main,
                         int left_angle_right, int right_angle_left,
                         int right_angle_main, int right_angle_right);
  void move_to_set_angles();
  void choose_pose(int pose);

private:
  std::array<int, 6> angles;
  std::array<int, 6> channels;
  Servo servos;
};
#endif
