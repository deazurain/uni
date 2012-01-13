// dependencies
#include <stdio.h>
#include "DBG.h"
#include "Motor.h"
#include "Sensor.h" 
#include "Button.h"
#include "Compass.h"
#include "GPIO2.h"

// the states
typedef enum PledgeState PledgeState;
enum PledgeState {
  PledgeState_FORWARD = 0,
  PledgeState_TO_HUG = 1,
  PledgeState_HUG = 2
};

// globals
int turn_count;
int F, L, R;
PledgeState state;
FILE * fout;

// help functions
void hugObstacle();
void calculateTurnCount();
void update();

// state functions
void doForward();
void doToHug();
void doHug();

int main() {
  // init
  Motor_init();
  Sensor_init();
  Button_init();
  Compass_init(); 
  fout = DBG_init();
  
  // start motors
  Motor_setForward();

  // beginstate
  state = PledgeState_FORWARD;
  
  while(1) {
    
    update(); // get new values from the hardware 

    switch(state) {
    case PledgeState_FORWARD:
      printf("PledgeState %d: forward\n", state);
      doForward();
      break;
    case PledgeState_TO_HUG:
      printf("PledgeState %d: about to hug\n", state);
      doToHug();
      break;
    case PledgeState_HUG:
      printf("PledgeState %d: hugging\n", state);
      doHug();
      break;
    }
  }

  // this will probably not run
  Motor_cleanup();
  Sensor_cleanup();
  Button_cleanup();
  DBG_cleanup();

}

// no obstacle ahead just keep heading north
void doForward() {

  int angle = Compass_getAngle();
  int l = 100, r = 100;

  // if the tank is slightly turning left -> steer right
  if(angle < 180) {
    l = (100 - (angle*20)/18);
    if(l < 10) l = 10;
  }
  else {
    r = (100 - ((360 - angle)*20)/18);
    if(r < 10) r = 10;
  }

  printf("Angle: %d\tl:%d\t, r:%d\n", angle, l, r);

  Motor_setLeft(l);
  Motor_setRight(r);
  
  // state transition rules
  // when an obstacle is near goto TO_HUG state
  if(F < 16) {
    state = PledgeState_TO_HUG;
  }

}

void doToHug() {

  Motor_LeftBackward();
  Motor_setRight(24);
  Motor_setLeft(24);

  // state transition rules
  // turn untill there is nothing in front of the tank 
  if(F > 24) {
    Motor_LeftForward();
    state = PledgeState_HUG;
  }
}

void doHug() {

  if(R < 15) {
     Motor_setRight(100);
     Motor_setLeft(40);
  }
  else if(R > 20) {
    printf("steering to right\n");
     Motor_setLeft(100);
     Motor_setRight(40);
  }
  else {
    Motor_setLeft(100);
    Motor_setRight(100);
  }

  // state transition rules
  if(F < 16) {
    state = PledgeState_TO_HUG;
  }
  else if(turn_count == 0) {
    state = PledgeState_FORWARD;
  }
}

int old_direction = 0;
int new_direction = 0;
int old_in_region = 1; // start in region
int new_in_region = 1;

/*
 * the idea is to have a region in which the count doesn't change. The count 
 * will only change upon leaving or entering this region centered around 
 * direction 0. 
 */

void calculateTurnCount() {

  old_direction = new_direction;
  new_direction = Compass_getAngle(); // the direction normalized on the starting direction

  old_in_region = new_in_region;
  new_in_region = new_direction < 30 || new_direction > 330;

  if(old_in_region) {
    if(new_in_region) {
      //stayed in region
      //do nothing
    }
    else {
      //left region
      if(new_direction < 180) {
        //left the region on the right side
        turn_count++;
      }
      else {
        //left the region on the left side
        turn_count--;
      }
    }
  }
  else { // old_in_region == false
    if(new_in_region) {
      //entered the region
      if(old_direction < 180) {
        //entered the region from the right side
        turn_count--;
      }
      else {
        //entered the region from the left side
        turn_count++;
      }
    }
    else {
      //stayed out of region
      //do nothing
    }
  }
}

void update() {
  writetomod();
  Sensor_update();
  Compass_update();

  calculateTurnCount();

  R = Sensor_getDistance(Sensor_RIGHT);
  if(R == 0) R = 999;

  int FL = Sensor_getDistance(Sensor_FRONT_LEFT);
  int FR = Sensor_getDistance(Sensor_FRONT_RIGHT);
  if(FL == 0) FL = 999;
  if(FR == 0) FR = 999;
  F = (FL < FR) ? FL : FR; // minimum value of front sensor values

  //printf("pledge update FL %d\tFR %d\tR %d\n", FL, FR, R);
  printf("F:%d\tR:%d\tDir:%d\tTurnCnt*2:%d\n", F, R, Compass_getDirection(), turn_count);

  //fprintf(fout, "Pledge.c\t sensors updated: F:%d, R:%d, Dir:%d\n, TurnCnt*2:%d", F, R, Compass_getDirection(), turn_count);
  fflush(fout);
}
