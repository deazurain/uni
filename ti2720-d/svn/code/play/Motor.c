/*
 * Motor.c
 *
 * Defines functions that control the engines in order to 
 * control the movement tank
 */

#include "Motor.h"


// dependencies

// #include "?"
#include "GPIO2.c"

void Motor_init(void){
	InitGPIO();
}
void Motor_cleanup(){
	CleanupGPIO();
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
ClearGPIOPin(5);
SetGPIOPin(6);
}
void Motor_RightBackward(){
ClearGPIOPin(6);
SetGPIOPin(5);
}
void Motor_LeftForward()
{
ClearGPIOPin(2);
SetGPIOPin(3);
}
void Motor_LeftBackward(){
ClearGPIOPin(3);
SetGPIOPin(2);
}
void Motor_setLeft(int percentage){
SetSpeedLeft(percentage);
}
void Motor_setRight(int percentage){
SetSpeedRight(percentage);
}