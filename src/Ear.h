#ifndef Ear_h
#define Ear_h

#include <Arduino.h>

class Ear {
public:
  void movetoangleposition(int angleLeft, int angleMain, int angleRight);
  void earsetup(int pinLeft, int pinMain, int pinRight);
  void movetoposition(int pose);

private:
};
#endif
