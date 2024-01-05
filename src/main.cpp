#include "Config.cpp"
#include "Ear.h"
#include "HardwareSerial.h"
#include <Arduino.h>

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

Ear leftear;
Ear rightear;

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
