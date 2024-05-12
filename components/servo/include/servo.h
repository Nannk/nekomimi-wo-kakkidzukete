#ifndef servo_h
#define servo_h

#include "config.h"
#include <array>
#include <cstdint>

struct Parameters {
  int angle;
  int channel;
};

class Servo {
public:
  void servo_init();
  void servo_rotate_to_angle(std::array<int, 6> &data);

private:
  uint32_t calc_duty_from_cycle(int angle);

  uint32_t duties[6] = {500, 500, 500, 500, 500, 500};
  uint32_t pins[6] = {14, 0, 12, /* left ear*/ 13, 2, 15 /*right ear*/};
  float phases[6] = {0, 0, 0, 0, 0, 0};
  std::array<Parameters, 6> persistent_params;
};
#endif // !servo_h
