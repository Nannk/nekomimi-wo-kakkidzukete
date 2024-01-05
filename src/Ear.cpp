#include "Ear.h"
#include <Arduino.h>
#include <Servo.h>

void Ear::earsetup(int pinLeft, int pinMain, int pinRight) {
  servoRight.attach(pinRight, 500, 2400);
  servoMain.attach(pinMain, 500, 2400);
  servoLeft.attach(pinLeft, 500, 2400);
}

void Ear::movetoangleposition(int angleLeft, int angleMain, int angleRight) {
  servoLeft.write(angleLeft);
  servoMain.write(angleMain);
  servoRight.write(angleRight);
}
