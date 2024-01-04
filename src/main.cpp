// does not compile
//"multiple definition of (thing from Config.cpp)"

#include "Config.cpp"
#include <Arduino.h>
#include <Ear.h>
#include <Pose.cpp>

int positionL = 0;
int positionR = 0;

unsigned long previosmillis = 0;

void setup() {
  pinMode(POTPIN1, INPUT);
  pinMode(POTPIN2, INPUT);

  leftear.earsetup(LLEFTWINGPIN, LMAINAXISPIN, LRIGHTWINGPIN);
  rightear.earsetup(RLEFTWINGPIN, RMAINAXISPIN, RRIGHTWINGPIN);

  previosmillis = millis();
}

void loop() {
  if (millis() - previosmillis >= 50) {
    previosmillis = millis();

    positionL = analogRead(POTPIN1);
    positionL = map(positionL, 0, 1023, 0, 180);

    positionR = analogRead(POTPIN2);
    positionR = map(positionR, 0, 1023, 0, 180);

    leftear.movetoangleposition(90, positionL, 90);
    rightear.movetoangleposition(90, positionR, 90);
  }
}
