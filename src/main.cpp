#include "Config.cpp"
#include "Ear.h"
#include "core_esp8266_features.h"
#include "poses.h"
#include <Adafruit_GFX.h>     //oled
#include <Adafruit_SSD1306.h> //oled
#include <Arduino.h>
#include <MPU9250_asukiaaa.h> //mpu
#include <Wire.h>             //mpu und oled
#include <arduinoFFT.h>       //fft
#include <cstdlib>

// Variables
Ear leftear;
Ear rightear;

int pose_number = 31;

// mpu
MPU9250_asukiaaa mpu;
float aX, aY, aZ, rateX, rateY, rateZ, mpuTemperature;
float corr_gyroX, corr_gyroY, corr_gyroZ, corr_aX, corr_aY, corr_aZ;

// fft
const uint16_t samples = 32;
const double samplingFrequency = 50;

float vReal[samples];
float vImag[samples];

ArduinoFFT<float> fft =
    ArduinoFFT<float>(vReal, vImag, samples, samplingFrequency);

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

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
  leftear.earsetup(LLEFTWINGPIN, LMAINAXISPIN, LRIGHTWINGPIN);
  rightear.earsetup(RLEFTWINGPIN, RMAINAXISPIN, RRIGHTWINGPIN);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true)
      ;
  }

  // dont need to set everything to 0 rn
  // for (float value : vImag) {
  //  value = 0.0;
  //}
  //

  calibration();
  mpusetup();

  previosmillis = millis();
}

void loop() {

  // put imu update here
  for (int i = 0; i < samples; i++) {
    while (mpu.gyroUpdate() != 0) {
      delay(1);
    }
    vReal[i] = mpu.gyroX() + corr_gyroX; // rateX
    vImag[i] = 0.0;
    // rateY = mpu.gyroY() + corr_gyroY;
    // rateZ = mpu.gyroZ() + corr_gyroZ;
  }

  fft.dcRemoval();
  fft.windowing(FFTWindow::Rectangle, FFTDirection::Forward); /* Weigh data*/
  fft.compute(FFTDirection::Forward);                         /* Compute*/
  fft.complexToMagnitude(); /* Compute magnitudes */

  if (millis() - previosmillis >= 10) {
    previosmillis = millis();

    oled.clearDisplay();
    for (int i = 0; i < samples / 2; i++) {
      oled.drawPixel(i * 4, 0.2 * vReal[i], WHITE);
    }
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(68, 5);
    oled.println(fft.majorPeak());
    oled.display();
  }
  /*
  if (mpu.accelUpdate() == 0) {
    aX = mpu.accelX() + corr_aX;
    aY = mpu.accelY() + corr_aY;
    aZ = mpu.accelZ() + corr_aZ;
  }
*/
  //  choosePose(pose_number, leftear, rightear);

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
