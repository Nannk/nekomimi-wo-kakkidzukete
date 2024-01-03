#ifndef Ear_h
#define Ear_h

#include <Arduino.h>
#include <Servo.h>

class Ear {
public:
  void movetoangleposition(int angleLeft, int angleMain, int angleRight);
  void earsetup(int pinLeft, int pinMain, int pinRight);
  void movetoposition(int pose);

private:
  Servo servoLeft;
  Servo servoMain;
  Servo servoRight;
};
#endif
