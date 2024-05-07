#ifndef servo_h
#define servo_h

#include "config.h"
#include <cstdint>

class Servo {
public:
  void servo_init(uint32_t pin[]);
  void servo_rotate_to_angle(int angle, int channel);

private:
  uint16_t calc_duty_from_cycle(int angle);
};
#endif // !servo_h
