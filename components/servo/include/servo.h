#ifndef servo_h
#define servo_h

#include <cstdint>

class Servo {
public:
  int servo_init(const uint8_t *pin);
  void servo_rotate_to_angle(int angle, int channel);
  int8_t channels[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

private:
  uint16_t calc_duty_from_cycle(int angle);
};
#endif // !servo_h
