#include "Config.cpp"
#include "Ear.h"
#include "HardwareSerial.h"
#include "Wire.h"
#include "c_types.h"
#include <Arduino.h>
#include <MPU9250_asukiaaa.h>
#include <arduinoFFT.h>

// Variables
Ear leftear;
Ear rightear;

// mpu
MPU9250_asukiaaa mpu;
float aX, aY, aZ, ratePitch, rateRoll, rateYaw, mpuTemperature;

// fft
arduinoFFT fft;
const uint16_t samples = 64;
const double sampling_frequency = 100;

unsigned long previosmillis = 0;

int pose = 31;

// custom functions

void choosePose(int poseNumber, Ear leftearf, Ear rightearf) {
  switch (poseNumber) {
  case 10:
    leftearf.movetoangleposition(106, 30, 26);
    rightearf.movetoangleposition(106, 150, 26);
    break;

  case 12:
    leftearf.movetoangleposition(53, 30, 79);
    rightearf.movetoangleposition(53, 150, 79);
    break;

  case 13:
    leftearf.movetoangleposition(132, 30, 132);
    rightearf.movetoangleposition(0, 150, 0);
    break;

  case 14:
    leftearf.movetoangleposition(0, 30, 0);
    rightearf.movetoangleposition(132, 150, 132);
    break;

  case 20:
    leftearf.movetoangleposition(106, 90, 26);
    rightearf.movetoangleposition(106, 90, 26);
    break;

  case 21:
    leftearf.movetoangleposition(0, 90, 132);
    rightearf.movetoangleposition(0, 90, 132);
    break;

  case 22:
    leftearf.movetoangleposition(53, 90, 79);
    rightearf.movetoangleposition(53, 90, 79);
    break;

  case 23:
    leftearf.movetoangleposition(132, 90, 132);
    rightearf.movetoangleposition(0, 90, 0);
    break;

  case 24:
    leftearf.movetoangleposition(0, 90, 0);
    rightearf.movetoangleposition(132, 90, 132);
    break;

  case 31:
    leftearf.movetoangleposition(0, 180, 132);
    rightearf.movetoangleposition(0, 0, 132);
    break;

  case 33:
    leftearf.movetoangleposition(0, 180, 0);
    rightearf.movetoangleposition(132, 0, 132);
    break;

  case 34:
    leftearf.movetoangleposition(132, 180, 132);
    rightearf.movetoangleposition(0, 0, 0);
    break;

  default:
    leftearf.movetoangleposition(0, 180, 132);
    rightearf.movetoangleposition(0, 0, 132);
    break;
  }
}

// possible calibration values because gyro has an offset, so it drifts quite
// heavily and accel has an offset too
void calibration() {}

void mpusetup() {
  Wire.begin();
  Wire.setClock(400000UL);

  mpu.beginGyro();
  mpu.beginAccel();
}

// main thingy
void setup() {
  Serial.begin(9600);

  leftear.earsetup(LLEFTWINGPIN, LMAINAXISPIN, LRIGHTWINGPIN);
  rightear.earsetup(RLEFTWINGPIN, RMAINAXISPIN, RRIGHTWINGPIN);

  mpusetup();

  Serial.println("setup done");
  previosmillis = millis();
}

void loop() {

  // put imu update here
  if (mpu.gyroUpdate() == 0) {
    Serial.print(mpu.gyroX());
    Serial.print(",");
    Serial.print(mpu.gyroY());
    Serial.print(",");
    Serial.print(mpu.gyroZ());
    Serial.print(",");
  }

  if (mpu.accelUpdate() == 0) {
    Serial.print(mpu.accelX());
    Serial.print(",");
    Serial.print(mpu.accelY());
    Serial.print(",");
    Serial.println(mpu.accelZ());
  }

  if (millis() - previosmillis >= 20) {
    previosmillis = millis();

    if (Serial.available()) {
      pose = Serial.parseInt();
      Serial.println(pose);

      choosePose(pose, leftear, rightear);
    }
  }
}
