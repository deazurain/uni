/*
 * LED.c
 *
 * Defines functions to read data from the LEDs
 * Als je leds wilt aansturen:
 *
 * LED_init()
 * LED_setState() aanroepen hoeveel je wilt
 * LED_cleanup
 */

#include "LED.h"
#include "HardwareConstants.h"
#include "user_gpio.h"

// dependencies

// #include "gpio.h" ???

//pre; GPIO_init()
int LED_init() {
  //return -1; // error
  SetGPIOPinDir(PIN_LED_LEFT, OUTPUT);
  SetGPIOPinDir(PIN_LED_RIGHT, OUTPUT);
  return 0;
}

int LED_cleanup() {
  SetGPIOPinDir(PIN_LED_LEFT, INPUT);
  SetGPIOPinDir(PIN_LED_RIGHT, INPUT);  
  return 0;
}

int LED_setState(int led_id, int state) {
  if(led_id == PIN_LED_LEFT){
    if(state){//== ON
      ClearGPIOPin(PIN_LED_LEFT);
    } else if(state == OFF){
      SetGPIOPin(PIN_LED_LEFT);
    }
  } else if(led_id == PIN_LED_RIGHT){   
    if(state){//== ON
      ClearGPIOPin(PIN_LED_RIGHT);
    } else if(state == OFF){
      SetGPIOPin(PIN_LED_RIGHT);
    }
  }
  return 0;
}
