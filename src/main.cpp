#include "Config.cpp"
#include "Ear.h"
#include "HardwareSerial.h" // Debug and data output
#include "poses.h" // Probably should rename to functions and move any misc functions there
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
const double sampling_frequency = 500;

float pitch_vReal[samples];
float pitch_vImag[samples];
float yaw_vReal[samples];
float yaw_vImag[samples];
float roll_vReal[samples];
float roll_vImag[samples];

ArduinoFFT<float> pitch_fft =
    ArduinoFFT<float>(pitch_vReal, pitch_vImag, samples, sampling_frequency);
ArduinoFFT<float> yaw_fft =
    ArduinoFFT<float>(pitch_vReal, pitch_vImag, samples, sampling_frequency);
ArduinoFFT<float> roll_fft =
    ArduinoFFT<float>(pitch_vReal, pitch_vImag, samples, sampling_frequency);

// Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

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

  mpu.beginGyro(GYRO_FULL_SCALE_500_DPS);
  // mpu.beginAccel();
}

// main thingy
void setup() {
  leftear.earsetup(LLEFTWINGPIN, LMAINAXISPIN, LRIGHTWINGPIN);
  rightear.earsetup(RLEFTWINGPIN, RMAINAXISPIN, RRIGHTWINGPIN);

  /*
   * Most definitely wont need this code anymore, its for i²c oled.
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true)
      ;
  }
*/

  calibration();
  mpusetup();

  Serial.begin(115200);
  previosmillis = millis();
}
/*
 * a wrapper around fft functions that computes fft and returns major peak.
 */
float perform_fft(ArduinoFFT<float> fft) {
  fft.dcRemoval();
  fft.windowing(FFTWindow::Rectangle, FFTDirection::Forward); // Weigh data
  fft.compute(FFTDirection::Forward);                         // Compute
  fft.complexToMagnitude(); // Compute magnitudes
  return fft.majorPeak();   // Return the frequency
}

void loop() {

  if (millis() - previosmillis >= 10) { // cap update @ 100Hz
    // get a frame of gyroscope data
    for (int i = 0; i < samples; i++) {
      while (mpu.gyroUpdate() != 0) {
        delay(1); // i dont like it. Should parallelize waiting for data and
                  // computing fft for previous data.
      }
      pitch_vReal[i] = mpu.gyroY() + corr_gyroY; // rateY
      roll_vReal[i] = mpu.gyroX() + corr_gyroX;  // rateX
      yaw_vReal[i] = mpu.gyroZ() + corr_gyroZ;   // rateZ

      pitch_vImag[i] = 0.0; // clear previous data
      roll_vImag[i] = 0.0;
      yaw_vImag[i] = 0.0;

      // rateY = mpu.gyroY() + corr_gyroY;
      // rateZ = mpu.gyroZ() + corr_gyroZ;
    }

    Serial.println(perform_fft(pitch_fft));
    Serial.println(perform_fft(roll_fft));
    Serial.println(perform_fft(yaw_fft));
    for (float real : pitch_vReal) {
      Serial.print(real);
    }
    Serial.println("");
    previosmillis = millis();
  }
  /*
   * Neiter this code, but ill leave it here for now.
  oled.clearDisplay();
  for (int i = 0; i < (samples / 2) - 1; i++) {
    oled.drawLine(i * 4, 0.1 * vReal[i], (i + 1) * 4, 0.1 * vReal[i + 1],
                  WHITE);
  }
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(68, 5);
  oled.println(fft.majorPeak());
  oled.display();
  */

  /*
  if (mpu.accelUpdate() == 0) {
    aX = mpu.accelX() + corr_aX;
    aY = mpu.accelY() + corr_aY;
    aZ = mpu.accelZ() + corr_aZ;
  }
  */

  // to move servos process what the anle should be,
  // use a "setter" function Ear::set_ear_position(int l, int m, int r)
  // then call Ear::move_to_set_angles() every 20ms (or 50ms) or so
}
