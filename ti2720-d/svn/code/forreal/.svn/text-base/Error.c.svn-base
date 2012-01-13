#include <unistd.h>
#include "Error.h"
#include "HardwareConstants.h"
#include "LED.h"





//accepts 2 bits (lsb) ddddddlr
int Error_set(unsigned char val){
  LED_setState(PIN_LED_LEFT, val&2);
  LED_setState(PIN_LED_RIGHT, val&1);  
  return 0;
}  

//pre; GPIO_init(), LED_init()
//accepts unsigned char;
//blinks msb first
//(left to right)
int Error_show(unsigned char val){
  Error_set(val>>6);
  sleep(1);
  Error_set(val>>4);
  sleep(1);
  Error_set(val>>2);
  sleep(1);
  Error_set(val);
  return 0;
}
  



