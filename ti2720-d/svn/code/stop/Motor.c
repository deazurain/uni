/*
 * Motor.c
 *
 * Defines functions that control the engines in order to 
 * control the movement tank
 */

#include "Motor.h"
#include "GPIO2.h"


// dependencies

// #include "?"

int Motor_init(void){
	InitGPIO2();
  return 0;
}
void Motor_cleanup(){
	CleanupGPIO2();
}
void Motor_stop(){
	SetSpeedRight(1);
	SetSpeedLeft(1);
}
void Motor_setForward()
{
Motor_RightForward();
Motor_LeftForward();

}
void Motor_setBackward(){
Motor_RightBackward();
Motor_LeftBackward();
}

void Motor_RightForward()
{
ClearGPIOPin2(5);
SetGPIOPin2(6);
}
void Motor_RightBackward(){
ClearGPIOPin2(6);
SetGPIOPin2(5);
}
void Motor_LeftForward()
{
ClearGPIOPin2(2);
SetGPIOPin2(3);
}
void Motor_LeftBackward(){
ClearGPIOPin2(3);
SetGPIOPin2(2);
}
void Motor_setLeft(int percentage){
SetSpeedLeft(percentage);
}
void Motor_setRight(int percentage){
SetSpeedRight(percentage);
}
