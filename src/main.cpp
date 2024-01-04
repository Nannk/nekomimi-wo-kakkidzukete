// does not compile
//"multiple definition of (thing from Config.cpp)"

#include "Config.cpp"
#include "HardwareSerial.h"
#include <Arduino.h>
#include <Ear.h>

int positionL = 0;
int positionR = 0;

Ear leftear;

Ear rightear;

void choosePose(int poseNumber, Ear leftear, Ear rightear) {
  switch (poseNumber) {
  case 10:
    leftear.movetoangleposition(106, 150, 26);
    rightear.movetoangleposition(106, 30, 26);

  case 12:
    leftear.movetoangleposition(53, 150, 79);
    rightear.movetoangleposition(53, 30, 79);

  case 13:
    leftear.movetoangleposition(132, 150, 132);
    rightear.movetoangleposition(0, 30, 0);

  case 14:
    leftear.movetoangleposition(0, 150, 0);
    rightear.movetoangleposition(132, 30, 132);

  case 20:
    leftear.movetoangleposition(106, 90, 26);
    rightear.movetoangleposition(106, 90, 26);

  case 21:
    leftear.movetoangleposition(0, 90, 132);
    rightear.movetoangleposition(0, 90, 132);

  case 22:
    leftear.movetoangleposition(53, 90, 79);
    rightear.movetoangleposition(53, 90, 79);

  case 23:
    leftear.movetoangleposition(132, 90, 132);
    rightear.movetoangleposition(0, 90, 0);

  case 24:
    leftear.movetoangleposition(0, 90, 0);
    rightear.movetoangleposition(132, 90, 132);

  case 31:
    leftear.movetoangleposition(0, 0, 132);
    rightear.movetoangleposition(0, 180, 132);

  case 33:
    leftear.movetoangleposition(0, 0, 0);
    rightear.movetoangleposition(132, 180, 132);

  case 34:
    leftear.movetoangleposition(132, 0, 132);
    rightear.movetoangleposition(0, 180, 0);
  default:
    leftear.movetoangleposition(0, 0, 132);
    rightear.movetoangleposition(0, 180, 132);
  }
}

unsigned long previosmillis = 0;
int pose = 31;

void setup() {
  Serial.begin(9600);

  leftear.earsetup(LLEFTWINGPIN, LMAINAXISPIN, LRIGHTWINGPIN);
  rightear.earsetup(RLEFTWINGPIN, RMAINAXISPIN, RRIGHTWINGPIN);

  previosmillis = millis();
}

void loop() {
  if (millis() - previosmillis >= 50) {
    previosmillis = millis();

    if (Serial.available()) {
      pose = Serial.parseInt();
      Serial.print("Pose Selected: ");
      Serial.println(pose);

      choosePose(pose, leftear, rightear);
    }

    /* unused old code
        positionL = analogRead(POTPIN1);
        positionL = map(positionL, 0, 1023, 0, 180);

        positionR = analogRead(POTPIN2);
        positionR = map(positionR, 0, 1023, 0, 180);

        leftear.movetoangleposition(90, positionL, 90);
        rightear.movetoangleposition(90, positionR, 90);
      */
  }
  delay(1);
}
