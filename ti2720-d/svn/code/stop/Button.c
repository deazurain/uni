#include "Button.h"
#include "HardwareConstants.h"
#include "user_gpio.h"

// standard component initialization and cleanup
int Button_init() {
  SetGPIOPinDir(PIN_BUTTON_LEFT, INPUT);
  SetGPIOPinDir(PIN_BUTTON_RIGHT, INPUT);  
  return 0;
}

int Button_cleanup() {
  // buttons moeten altijd listenen dus deze functie wordt niet aangeroepen.
  return 0; 
}

/* Getstate returnwaarden
00 geen knoppen ingedrukt
01 rechterknop ingedrukt
10 linkerknop ingedrukt
11 beide knoppen ingedrukt
*/
int Button_getState() 
{
  int leftButton = GetGPIOPin(PIN_BUTTON_LEFT);  
  int rightButton = GetGPIOPin(PIN_BUTTON_RIGHT);

  return leftButton * 10 + rightButton;
}


