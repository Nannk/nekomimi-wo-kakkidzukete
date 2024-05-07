#include "ear.h"
#include "servo.h"
#include <cstdint>

// #include <Servo.h>
/*
#define TIMER_INTERRUPT_DEBUG 0
#define ISR_SERVO_DEBUG 0
*/

#define MIN_MICROS 500
#define MAX_MICROS 2400

void Ear::earsetup(int pin_left, int pin_main, int pin_right) {

  channel_left = Ear::servos.servo_init((uint8_t *)pin_left);
  channel_main = Ear::servos.servo_init((uint8_t *)pin_main);
  channel_right = Ear::servos.servo_init((uint8_t *)pin_right);

  //  servoindex1 = ISR_Servo.setupServo(pin_left, MIN_MICROS, MAX_MICROS);
  //  servoindex2 = ISR_Servo.setupServo(pin_main, MIN_MICROS, MAX_MICROS);
  //  servoindex3 = ISR_Servo.setupServo(pin_right, MIN_MICROS, MAX_MICROS);
  // servo_right.attach(pinRight, 500, 2400);
  // servo_main.attach(pinMain, 500, 2400);
  // servo_left.attach(pinLeft, 500, 2400);
}

void Ear::set_ear_position(int angle_left, int angle_main, int angle_right) {
  Ear::angle_left = angle_left;
  Ear::angle_main = angle_main;
  Ear::angle_right = angle_right;
}

void Ear::move_to_set_angles() {
  servos.servo_rotate_to_angle(angle_left, channel_left);
  servos.servo_rotate_to_angle(angle_main, channel_main);
  servos.servo_rotate_to_angle(angle_right, channel_right);

  //  Ear::movetoangleposition(Ear::angle_left, Ear::angle_main,
  //  Ear::angle_right);
  // ISR_Servo.setPosition(servoindex1, angle_left);
  // ISR_Servo.setPosition(servoindex2, angle_main);
  // ISR_Servo.setPosition(servoindex3, angle_right);

  // servo_left.write(angleLeft);
  // servo_main.write(angleMain);
  // servo_right.write(angleRight);
}
