#include "ear.h"
#include "servo.h"
#include <cstdint>
#include <cstdio>
#include <sys/types.h>

// #include <Servo.h>
/*
#define TIMER_INTERRUPT_DEBUG 0
#define ISR_SERVO_DEBUG 0
*/
//  servoindex1 = ISR_Servo.setupServo(pin_left, MIN_MICROS, MAX_MICROS);
//  servoindex2 = ISR_Servo.setupServo(pin_main, MIN_MICROS, MAX_MICROS);
//  servoindex3 = ISR_Servo.setupServo(pin_right, MIN_MICROS, MAX_MICROS);
// servo_right.attach(pinRight, 500, 2400);
// servo_main.attach(pinMain, 500, 2400);
// servo_left.attach(pinLeft, 500, 2400);
void Ear::ear_init(int lch, int mch, int rch) {
  channel_left = lch;
  channel_main = mch;
  channel_right = rch;
}

void Ear::set_ear_position(int angle_left, int angle_main, int angle_right) {
  ear_angle_left = angle_left;
  ear_angle_main = angle_main;
  ear_angle_right = angle_right;
}

void Ear::move_to_set_angles(Servo servos) {
  servos.servo_rotate_to_angle(ear_angle_left, channel_left);
  servos.servo_rotate_to_angle(ear_angle_main, channel_main);
  servos.servo_rotate_to_angle(ear_angle_right, channel_right);
}

void Ear::print_angles_debug() {
  printf("%d %d %d\n", ear_angle_right, ear_angle_main, ear_angle_left);
}

//  Ear::movetoangleposition(Ear::angle_left, Ear::angle_main,
//  Ear::angle_right);
// ISR_Servo.setPosition(servoindex1, angle_left);
// ISR_Servo.setPosition(servoindex2, angle_main);
// ISR_Servo.setPosition(servoindex3, angle_right);

// servo_left.write(angleLeft);
// servo_main.write(angleMain);
// servo_right.write(angleRight);
