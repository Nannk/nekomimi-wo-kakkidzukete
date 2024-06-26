#ifndef Ear_h
#define Ear_h

#include <Arduino.h>
// #include <Servo.h>

class Ear {
public:
  void earsetup(int pin_left, int pin_main, int pin_right);
  void set_ear_position(int angle_left, int angle_main, int angle_right);
  void move_to_set_angles();

private:
  // ISR_Servo servo_left;
  // ISR_Servo servo_main;
  // ISR_Servo servo_right;
  int angle_left;
  int angle_main;
  int angle_right;

  int servoindex1 = -1;
  int servoindex2 = -1;
  int servoindex3 = -1;
};
#endif
