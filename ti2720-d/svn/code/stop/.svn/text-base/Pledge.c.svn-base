#include <stdio.h>
#include "DBG.h"
#include "Motor.h"
#include "Sensor.h" 
#include "Button.h"
#include "Compass.h"

int turnCount;

int F, L, R;

void hugObstacle();
void calculateTurnCount();
void update();

FILE * fout;

int main(int argc, char * argv[]) {
  int forward;
  int left;
  int right;
  
  Motor_init();
  Sensor_init();
  Button_init();
  Compass_init(); 

  if(argc != 4) {
    Motor_stop();
    return 0;
  }

  forward = atoi(argv[1]);
  left = atoi(argv[2]);
  right = atoi(argv[3]);

  if(forward) {
    Motor_setForward();
  }
  else {
    Motor_setBackward();
  }
  Motor_setRight(right);
  Motor_setLeft(left);
 

  sleep(5);

  Motor_stop();
}

