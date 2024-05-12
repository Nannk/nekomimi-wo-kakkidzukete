#ifndef Ear_h
#define Ear_h

#include "servo.h"
#include <sys/types.h>
class Ear {
  /*
   Ear(Ear &) = delete;
   Ear &operator=(Ear &) = delete;
   Ear(Ear &&mE) = default;
   Ear &operator=(Ear &&mE) = default;
 */
public:
  void ear_init(int lch, int mch, int rch);
  void set_ear_position(int angle_left, int angle_main, int angle_right);
  void move_to_set_angles(Servo servos);
  void print_angles_debug();

private:
  // servo values
  int ear_angle_left;
  int ear_angle_main;
  int ear_angle_right;
  // servo channels
  int channel_left;
  int channel_main;
  int channel_right;
  // Debug
};
#endif
