/*
#include "Motor.h"
#include "Sensor.h" 
#include "Button.h"
#include "Compass.h"
#include "user_gpio2.c"

int turnCount;

int F, L, R;

void hugObstacle();
void calculateTurnCount();

int main(int argc, char **argv) {

	Motor_init();
	Sensor_init();
	Button_init();
	Compass_init(); 
	
	turnCount = 0;

	while(Button_getState(Button_GREEN == 1)
		;
	
	while(Button_getState(Button_ORANGE == 1) {
		Sensor_update();
		F = (Sensor_getDistance(Sensor_FRONT_LEFT) +
				Sensor_getDistance(Sensor_FRONT_RIGHT)) / 2;
		R = Sensor_getDistance(Sensor_RIGHT);
		L = Sensor_getDistance(Sensor_LEFT);
		
		while(front > 20) {
			
			if(Compass_inRange(15, 180))
				Motor_steerLeft(0.9);
			else if(Compass_inRange(180, 345))
				Motor_steerRight(0.9);
			else
				Motor_goForward();
		}
		
		hugObstacle();
	}
	
	Motor_cleanup();
	Sensor_cleanup();
	Button_cleanup();
        Compass_cleanup();
}

	
void hugObstacle() {
		
	while(!(Compass_inRange(340, 20) && turnCount == 0)) {
		int right = Sensor_getDistance(Sensor_RIGHT);
		int left = Sensor_getDistance(Sensor_LEFT);
		int front = (Sensor_getDistance(Sensor_FRONT_LEFT) + 
				Sensor_getDistance(Sensor_FRONT_RIGHT)) / 2;
		
		
		if(right < 10)
			Motor_steerLeft(0.9);
		else if(right< 30) {
			if(front > 20)
				Motor_goForward();
			else
				Motor_turnLeft();
		}
		else if(right < 40)
			Motor_steerRight(0.9);	
		else
			Motor_turnRight();
		
		calculateTurnCount();
	}
}

void calculateTurnCount() {
	int oldDir = turnCount * 90;
	if(Compass_inRange(oldDir + 70, oldDir + 110))
		turnCount++;
	else if(Compass_inRange(oldDir + 250, oldDir + 290))
		turnCount--;
}*/
