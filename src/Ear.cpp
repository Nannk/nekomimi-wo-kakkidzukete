#include "Ear.h"
#include <Arduino.h>
#include <ESP8266_ISR_Servo.h>
// #include <Servo.h>

#define MIN_MICROS 500
#define MAX_MICROS 2400

void Ear::earsetup(int pinLeft, int pinMain, int pinRight) {
  servoindex1 = ISR_Servo.setupServo(pinLeft, MIN_MICROS, MAX_MICROS);
  servoindex2 = ISR_Servo.setupServo(pinMain, MIN_MICROS, MAX_MICROS);
  servoindex3 = ISR_Servo.setupServo(pinRight, MIN_MICROS, MAX_MICROS);
  // servoRight.attach(pinRight, 500, 2400);
  // servoMain.attach(pinMain, 500, 2400);
  // servoLeft.attach(pinLeft, 500, 2400);
}

void Ear::movetoangleposition(int angleLeft, int angleMain, int angleRight) {
  if (servoindex1 != -1 && servoindex2 != -1 && servoindex3 != -1) {
    ISR_Servo.setPosition(servoindex1, angleLeft);
    ISR_Servo.setPosition(servoindex2, angleMain);
    ISR_Servo.setPosition(servoindex3, angleRight);
  }

  // servoLeft.write(angleLeft);
  // servoMain.write(angleMain);
  // servoRight.write(angleRight);
}
