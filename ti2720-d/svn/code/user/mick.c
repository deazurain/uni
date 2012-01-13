#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "user_gpio.h"

const int PIN_LEFT_MOTOR_ENABLED = 4;
const int PIN_LEFT_MOTOR_FORWARD = 3;
const int PIN_LEFT_MOTOR_REVERSE = 2;

const int PIN_RIGHT_MOTOR_ENABLED = 7;
const int PIN_RIGHT_MOTOR_FORWARD = 6;
const int PIN_RIGHT_MOTOR_REVERSE = 5;

const int PIN_ORANGE_BUTTON = 8;
const int PIN_GREEN_BUTTON = 9;

const int PIN_ORANGE_LED = 8;
const int PIN_GREEN_LED = 9;

/*
#define PIN_LEFT_MOTOR_ENABLE 4
#define PIN_LEFT_MOTOR_FORWARD 3
#define PIN_LEFT_MOTOR_REVERSE 2

#define PIN_RIGHT_MOTOR_ENABLE 7
#define PIN_RIGHT_MOTOR_FORWARD 6
#define PIN_RIGHT_MOTOR_REVERSE 5

#define PIN_ORANGE_BUTTON 8
#define PIN_GREEN_BUTTON 9

#define PIN_ORANGE_LED 8
#define PIN_GREEN_LED 9
*/

void print_motor_status() {
  int enabled = -1;
  int forward = -1;
  int reverse = -1;

  // left motor
  enabled = GetGPIOPin(PIN_LEFT_MOTOR_ENABLED);
  forward = GetGPIOPin(PIN_LEFT_MOTOR_FORWARD);
  reverse = GetGPIOPin(PIN_LEFT_MOTOR_REVERSE);
  printf("left\n  enabled %d\n  forward %d\n  reverse %d\n");
  
  // right motor
  enabled = GetGPIOPin(PIN_RIGHT_MOTOR_ENABLED);
  forward = GetGPIOPin(PIN_RIGHT_MOTOR_FORWARD);
  reverse = GetGPIOPin(PIN_RIGHT_MOTOR_REVERSE);
  printf("right\n  enabled %d\n  forward %d\n  reverse %d\n");
}

void print_button_status() {
  printf("orange %d\ngreen %d\n", GetGPIOPin(PIN_ORANGE_BUTTON), GetGPIOPin(PIN_GREEN_BUTTON));
}
  

int main(int argc, char **argv) {
 
  InitGPIO();

  while(1) {
    print_motor_status();
    print_button_status();

    /*
    int * pins = (int *) malloc(sizeof(int) * 22);
    int i = 0;
    while(i < 22) {
      pins[i] = GetGPIOPin(i);

      printf("%d ", pins[i]);
      i++;
    }

    printf("\n");
    */

    sleep(1);
    
  }

  CleanupGPIO();
  CleanupPPC();

  return 0;
}


