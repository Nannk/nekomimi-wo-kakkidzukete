#pragma once
#include "Ear.h"
#include <Arduino.h>
#include <Servo.h>

void Ear::earsetup(int pinLeft, int pinMain, int pinRight) {
  servoRight.attach(pinRight);
  servoMain.attach(pinMain);
  servoLeft.attach(pinLeft);
}

void Ear::movetoangleposition(int angleLeft, int angleMain, int angleRight) {
  servoLeft.write(angleLeft);
  servoMain.write(angleMain);
  servoRight.write(angleRight);
}
