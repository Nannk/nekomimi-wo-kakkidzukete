#include "Config.cpp"
#include "Ear.h"
#include "HardwareSerial.h"
#include "Wire.h"
#include <Arduino.h>
#include <MPU9250_asukiaaa.h>
#include <arduinoFFT.h>

// Variables
Ear leftear;
Ear rightear;

// mpu
MPU9250_asukiaaa mpu;
float aX, aY, aZ, rateX, rateY, rateZ, mpuTemperature;
float corr_gyroX, corr_gyroY, corr_gyroZ, corr_aX, corr_aY, corr_aZ;

// fft
arduinoFFT fft;
const uint16_t samples = 64;
const double sampling_frequency = 100;

unsigned long previosmillis = 0;

int pose = 31;

// TODO put this in a separate file
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
void calibration() {
  corr_gyroX = -1.647184035;
  corr_gyroY = 0.7031929047;
  corr_gyroZ = -0.4409756098;
  corr_aX = 0.00711751663;
  corr_aY = 0.05541019956;
  corr_aZ = 0.1359201774;
}

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

  calibration();

  mpusetup();

  Serial.println("setup done");
  previosmillis = millis();
}

void loop() {

  // put imu update here
  if (mpu.gyroUpdate() == 0) {

    rateX = mpu.gyroX() + corr_gyroX;
    rateY = mpu.gyroY() + corr_gyroY;
    rateZ = mpu.gyroZ() + corr_gyroZ;
  }
  if (mpu.accelUpdate() == 0) {
    aX = mpu.accelX() + corr_aX;
    aY = mpu.accelY() + corr_aY;
    aZ = mpu.accelZ() + corr_aZ;
  }

  ///
  Serial.print(rateX);
  Serial.print(",");
  Serial.print(rateY);
  Serial.print(",");
  Serial.print(rateZ);
  Serial.print(",");

  Serial.print(aX);
  Serial.print(",");
  Serial.print(aY);
  Serial.print(",");
  Serial.println(aZ);
  /*
    if (millis() - previosmillis >= 20) {
      previosmillis = millis();
          if (Serial.available()) {
            pose = Serial.parseInt();
            Serial.println(pose);
      choosePose(pose, leftear, rightear);
    }
    }
    */
}
