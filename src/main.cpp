#include <Arduino.h>
#include <Ear.h>
#include <Servo.h>

// Left
int LLEFTWINGPIN = 2;
int LMAINAXISPIN = 1;
int LRIGHTWINGPIN = 3;
Ear leftear;

// Right
int RLEFTWINGPIN = 2;
int RMAINAXISPIN = 1;
int RRIGHTWINGPIN = 3;
Ear rightear;

int position = 0;
unsigned long previosmillis = 0;

void setup() {
  leftear.earsetup(LLEFTWINGPIN, LMAINAXISPIN, LRIGHTWINGPIN);
  rightear.earsetup(RLEFTWINGPIN, RMAINAXISPIN, RRIGHTWINGPIN);
}

void loop() {
  previosmillis = millis();
  for (int position = 0; position <= 180; position++) {
    if (millis() - previosmillis >= 15) {
      previosmillis = millis();
      leftear.movetoangleposition(90, position, 90);
      rightear.movetoangleposition(90, position, 90);
    }
  }
}
