#ifndef Ear_h
#define Ear_h

#include "servo.h"
class Ear {
public:
  void earsetup(int pin_left, int pin_main, int pin_right);
  void set_ear_position(int angle_left, int angle_main, int angle_right);
  void move_to_set_angles();

private:
  // ISR_Servo servo_left;
  // ISR_Servo servo_main;
  // ISR_Servo servo_right;
  Servo servos;
  int angle_left;
  int angle_main;
  int angle_right;
  int channel_left;
  int channel_main;
  int channel_right;
};
#endif
