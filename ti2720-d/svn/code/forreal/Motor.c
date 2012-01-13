/*
 * Motor.c
 *
 * Defines functions that control the engines in order to 
 * control the movement tank
 */

#include "Motor.h"
#include "GPIO2.h"
#include "HardwareConstants.h"


// dependencies

// #include "?"
#include "GPIO2.h"

int Motor_init(void) {
  InitGPIO2();
  return 0;
}

void Motor_cleanup() {
  CleanupGPIO2();
}

void Motor_stop() {
  SetSpeedRight(1);
  SetSpeedLeft(1);
}

void Motor_setForward() {
  Motor_RightForward();
  Motor_LeftForward();
}

void Motor_setBackward() {
  Motor_RightBackward();
  Motor_LeftBackward();
}

void Motor_RightForward() {
  ClearGPIOPin2(PIN_ENGINE_RIGHT_BACKWARD);
  SetGPIOPin2(PIN_ENGINE_RIGHT_FORWARD);
}

void Motor_RightBackward() {
  ClearGPIOPin2(PIN_ENGINE_RIGHT_FORWARD);
  SetGPIOPin2(PIN_ENGINE_RIGHT_BACKWARD);
}

void Motor_LeftForward() {
  ClearGPIOPin2(PIN_ENGINE_LEFT_BACKWARD);
  SetGPIOPin2(PIN_ENGINE_LEFT_FORWARD);
}

void Motor_LeftBackward() {
  ClearGPIOPin2(PIN_ENGINE_LEFT_FORWARD);
  SetGPIOPin2(PIN_ENGINE_LEFT_BACKWARD);
}

void Motor_setLeft(int percentage) {
  SetSpeedLeft(percentage);
}

void Motor_setRight(int percentage) {
  SetSpeedRight(percentage);
}
