#ifndef servo_h
#define servo_h

#include "config.h"
#include <cstdint>

struct Parameters {
  int angle;
  int channel;
};

class Servo {
public:
  void servo_init();
  void servo_rotate_to_angle(int angle, int channel);

private:
  uint32_t duties[6] = {500, 500, 500, 500, 500, 500};
  uint32_t pins[6] = {14, 0, 12 /* left ear*/,
                      13, 2, 15 /*right ear*/}; //{14, 0, 12, 13, 2, 15};
  float phases[6] = {0, 0, 0, 0, 0, 0};
  uint16_t calc_duty_from_cycle(int angle);
  Parameters *persistent_data = new Parameters[6];
};
#endif // !servo_h
