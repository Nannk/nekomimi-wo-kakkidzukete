#include <Arduino.h>
#include <Ear.h>

// This function sets servos to the pre-determinde postions.
// To denfine your own positions, use Ear::movetoangleposition()
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
