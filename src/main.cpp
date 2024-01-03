#include <Arduino.h>
#include <Ear.h>
#include <Servo.h>

// Left
int LLEFTWINGPIN = 3;
int LMAINAXISPIN = 5;
int LRIGHTWINGPIN = 6;
Ear leftear;

// Right
int RLEFTWINGPIN = 9;
int RMAINAXISPIN = 10;
int RRIGHTWINGPIN = 11;
Ear rightear;

int position = 0;
unsigned long previosmillis = 0;

void setup() {
  leftear.earsetup(LLEFTWINGPIN, LMAINAXISPIN, LRIGHTWINGPIN);
  rightear.earsetup(RLEFTWINGPIN, RMAINAXISPIN, RRIGHTWINGPIN);
  previosmillis = millis();
}

void loop() {
  // previosmillis = millis();
  for (int position = 0; position <= 180; position++) {
    // if (millis() - previosmillis >= 1000) {
    previosmillis = millis();
    leftear.movetoangleposition(90, position, 90);
    rightear.movetoangleposition(90, position, 90);
    delay(100);
    //}
  }
  delay(500);
}
