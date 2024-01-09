#include "Config.cpp"
#include "Ear.h"
#include "HardwareSerial.h"
#include "MPU9250/QuaternionFilter.h"
#include <Arduino.h>
#include <MPU9250.h>

// Variables

Ear leftear;
Ear rightear;

MPU9250 mpu;

MPU9250Setting mpusetting;

unsigned long previosmillis = 0;

int pose = 31;
float aX, aY, aZ, ratePitch, rateRoll, rateYaw, mpuTemperature;

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

void mpusetup() {

  Wire.begin();

  mpusetting.accel_fs_sel = ACCEL_FS_SEL::A8G;
  mpusetting.gyro_fs_sel = GYRO_FS_SEL::G1000DPS;
  mpusetting.fifo_sample_rate = FIFO_SAMPLE_RATE::SMPL_500HZ;
  mpusetting.gyro_fchoice = 0x03;
  mpusetting.gyro_dlpf_cfg = GYRO_DLPF_CFG::DLPF_250HZ;
  mpusetting.accel_fchoice = 0x01;
  mpusetting.accel_dlpf_cfg = ACCEL_DLPF_CFG::DLPF_99HZ;

  mpu.selectFilter(QuatFilterSel::NONE); // filter outputs zeroes

  mpu.setup(0x68, mpusetting);
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

  if (mpu.update()) {
    // TODO serialprints should are for testing only and should be removed as
    // servo lib lags
    Serial.print(mpu.getPitch());
    Serial.print(",");
    Serial.print(mpu.getYaw());
    Serial.print(",");
    Serial.println(mpu.getRoll());
    // Serial.print(",");
    /*
          Serial.print(mpu.getAccX());
          Serial.print(",");
          Serial.print(mpu.getAccY());
          Serial.print(",");
          Serial.print(mpu.getAccZ());
          Serial.print(",");
    */
    // Serial.println(mpu.getTemperature());
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
