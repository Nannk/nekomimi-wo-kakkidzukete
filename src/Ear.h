#ifndef Ear_h
#define Ear_h

#include <Arduino.h>
// #include <Servo.h>

class Ear {
public:
  void movetoangleposition(int angleLeft, int angleMain, int angleRight);
  void earsetup(int pinLeft, int pinMain, int pinRight);

private:
  // ISR_Servo servoLeft;
  // ISR_Servo servoMain;
  // ISR_Servo servoRight;
  int servoindex1 = -1;
  int servoindex2 = -1;
  int servoindex3 = -1;
};
#endif
