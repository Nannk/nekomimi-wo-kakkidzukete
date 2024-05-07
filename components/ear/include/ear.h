#ifndef Ear_h
#define Ear_h

#include "servo.h"
#include <sys/types.h>
class Ear {
public:
  void ear_init(int lch, int mch, int rch);
  void set_ear_position(int angle_left, int angle_main, int angle_right);
  void move_to_set_angles(Servo servos);

private:
  // ISR_Servo servo_left;
  // ISR_Servo servo_main;
  // ISR_Servo servo_right;
  int angle_left;
  int angle_main;
  int angle_right;
  int channel_left;
  int channel_main;
  int channel_right;
};
#endif
