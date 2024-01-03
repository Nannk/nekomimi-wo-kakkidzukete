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

// probably make pose enum?
// or just write a function for each pose
void Ear::movetoposition(int pose) {
  switch (pose) {
  case 0:
    movetoangleposition(90, 90, 90);
    break;

  case 1:
    movetoangleposition(90, 180, 90);
    break;
  }
}
