// does not compile
//"multiple definition of (thing from Config.cpp)"

#include "Config.cpp"
#include "HardwareSerial.h"
#include <Arduino.h>
#include <Ear.h>

void choosePose(int poseNumber, Ear leftearf, Ear rightearf) {
  switch (poseNumber) {
  case 10:
    leftearf.movetoangleposition(106, 150, 26);
    rightearf.movetoangleposition(106, 30, 26);

  case 12:
    leftearf.movetoangleposition(53, 150, 79);
    rightearf.movetoangleposition(53, 30, 79);

  case 13:
    leftearf.movetoangleposition(132, 150, 132);
    rightearf.movetoangleposition(0, 30, 0);

  case 14:
    leftearf.movetoangleposition(0, 150, 0);
    rightearf.movetoangleposition(132, 30, 132);

  case 20:
    leftearf.movetoangleposition(106, 90, 26);
    rightearf.movetoangleposition(106, 90, 26);

  case 21:
    leftearf.movetoangleposition(0, 90, 132);
    rightearf.movetoangleposition(0, 90, 132);

  case 22:
    leftearf.movetoangleposition(53, 90, 79);
    rightearf.movetoangleposition(53, 90, 79);

  case 23:
    leftearf.movetoangleposition(132, 90, 132);
    rightearf.movetoangleposition(0, 90, 0);

  case 24:
    leftearf.movetoangleposition(0, 90, 0);
    rightearf.movetoangleposition(132, 90, 132);

  case 31:
    leftearf.movetoangleposition(0, 0, 132);
    rightearf.movetoangleposition(0, 180, 132);

  case 33:
    leftearf.movetoangleposition(0, 0, 0);
    rightearf.movetoangleposition(132, 180, 132);

  case 34:
    leftearf.movetoangleposition(132, 0, 132);
    rightearf.movetoangleposition(0, 180, 0);

  default:
    leftearf.movetoangleposition(0, 0, 132);
    rightearf.movetoangleposition(0, 180, 132);
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

  // previosmillis = millis();
}

void loop() {
  // previosmillis = millis();
  /*
    if (Serial.available()) {
      pose = Serial.parseInt();
      Serial.print("Pose Selected: ");
      Serial.println(pose);

      choosePose(pose, leftear, rightear);
    }
    */
  choosePose(10, leftear, rightear);
  delay(200);

  choosePose(22, leftear, rightear);
  delay(200);

  choosePose(34, leftear, rightear);
  delay(200);

  choosePose(24, leftear, rightear);
  delay(200);

  /* unused old code
      positionL = analogRead(POTPIN1);
      positionL = map(positionL, 0, 1023, 0, 180);

      positionR = analogRead(POTPIN2);
      positionR = map(positionR, 0, 1023, 0, 180);

      leftear.movetoangleposition(90, positionL, 90);
      rightear.movetoangleposition(90, positionR, 90);
    */
}
