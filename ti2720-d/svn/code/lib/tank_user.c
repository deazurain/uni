#include "tank_user.h"
#include "user_gpio.h"

// motor wrapper functions
void InitMotor(){
  SetGPIOPinDir(LEFT_REVERSE, 1);
  SetGPIOPinDir(LEFT_FORWARD, 1);
  SetGPIOPinDir(LEFT_ENABLE, 1);
  SetGPIOPinDir(RIGHT_REVERSE, 1);
  SetGPIOPinDir(RIGHT_FORWARD, 1);
  SetGPIOPinDir(RIGHT_ENABLE, 1);

  Halt();

  SetGPIOPin(LEFT_ENABLE);
  SetGPIOPin(RIGHT_ENABLE);
}

void Forward(){
  ClearGPIOPin(LEFT_REVERSE);
  SetGPIOPin(LEFT_FORWARD);
  ClearGPIOPin(RIGHT_REVERSE);
  SetGPIOPin(RIGHT_FORWARD);
}

void Backward(){
  ClearGPIOPin(LEFT_FORWARD);
  SetGPIOPin(LEFT_REVERSE);
  ClearGPIOPin(RIGHT_FORWARD);
  SetGPIOPin(RIGHT_REVERSE);
}

void TurnLeft(){
  ClearGPIOPin(LEFT_FORWARD);
  ClearGPIOPin(LEFT_REVERSE);
  ClearGPIOPin(RIGHT_REVERSE);
  SetGPIOPin(RIGHT_FORWARD);
}
void TurnRight(){
  ClearGPIOPin(RIGHT_FORWARD);
  ClearGPIOPin(RIGHT_REVERSE);
  ClearGPIOPin(LEFT_REVERSE);
  SetGPIOPin(LEFT_FORWARD);
}
void RightInPlace(){
  ClearGPIOPin(RIGHT_FORWARD);
  SetGPIOPin(RIGHT_REVERSE);
  ClearGPIOPin(LEFT_REVERSE);
  SetGPIOPin(LEFT_FORWARD);
}

void LeftInPlace(){
  ClearGPIOPin(LEFT_FORWARD);
  SetGPIOPin(LEFT_REVERSE);
  ClearGPIOPin(RIGHT_REVERSE);
  SetGPIOPin(RIGHT_FORWARD);
}

void Halt(){
  ClearGPIOPin(LEFT_REVERSE);
  ClearGPIOPin(LEFT_FORWARD);
  ClearGPIOPin(RIGHT_REVERSE);
  ClearGPIOPin(RIGHT_FORWARD);
}

void Off(){
  Halt();
  ClearGPIOPin(LEFT_ENABLE);
  ClearGPIOPin(RIGHT_ENABLE);
}

// led wrapper functions
void initLEDS();
void enableOLED();
void enableGLED();
void disableOLED();
void disableGLED();










#endif

