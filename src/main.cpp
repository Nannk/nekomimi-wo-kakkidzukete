#include "Config.cpp"
#include "Ear.h"
#include "HardwareSerial.h"
#include "Wire.h"
#include "poses.h"
#include <Arduino.h>
#include <MPU9250_asukiaaa.h>
#include <arduinoFFT.h>

// Variables
Ear leftear;
Ear rightear;

int pose_number = 31;

// mpu
MPU9250_asukiaaa mpu;
float aX, aY, aZ, rateX, rateY, rateZ, mpuTemperature;
float corr_gyroX, corr_gyroY, corr_gyroZ, corr_aX, corr_aY, corr_aZ;

// fft
arduinoFFT fft;
const uint16_t samples = 64;
const double sampling_frequency = 100;

unsigned long previosmillis = 0;

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
  // calibration();

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

  choosePose(pose_number, leftear, rightear);

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

  // do not use choosepose,
  // make an "angle variable",
  // process what it should be,
  //  movetoposion at the end every like 40 ms or so
}
