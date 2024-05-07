#include "ear.h"

// This function sets angles to the pre-determinde postions.
// To denfine your own positions, use Ear::set_ear_position()
void choose_pose(int poseNumber, Ear leftear, Ear rightear) {
  switch (poseNumber) {
  case 10:
    leftear.set_ear_position(106, 30, 26);
    rightear.set_ear_position(106, 150, 26);
    break;

  case 12:
    leftear.set_ear_position(53, 30, 79);
    rightear.set_ear_position(53, 150, 79);
    break;

  case 13:
    leftear.set_ear_position(132, 30, 132);
    rightear.set_ear_position(0, 150, 0);
    break;

  case 14:
    leftear.set_ear_position(0, 30, 0);
    rightear.set_ear_position(132, 150, 132);
    break;

  case 20:
    leftear.set_ear_position(106, 90, 26);
    rightear.set_ear_position(106, 90, 26);
    break;

  case 21:
    leftear.set_ear_position(0, 90, 132);
    rightear.set_ear_position(0, 90, 132);
    break;

  case 22:
    leftear.set_ear_position(53, 90, 79);
    rightear.set_ear_position(53, 90, 79);
    break;

  case 23:
    leftear.set_ear_position(132, 90, 132);
    rightear.set_ear_position(0, 90, 0);
    break;

  case 24:
    leftear.set_ear_position(0, 90, 0);
    rightear.set_ear_position(132, 90, 132);
    break;

  case 31:
    leftear.set_ear_position(0, 180, 132);
    rightear.set_ear_position(0, 0, 132);
    break;

  case 33:
    leftear.set_ear_position(0, 180, 0);
    rightear.set_ear_position(132, 0, 132);
    break;

  case 34:
    leftear.set_ear_position(132, 180, 132);
    rightear.set_ear_position(0, 0, 0);
    break;

  default:
    leftear.set_ear_position(0, 180, 132);
    rightear.set_ear_position(0, 0, 132);
    break;
  }
}
