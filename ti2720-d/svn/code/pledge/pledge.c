#include "Motor.h"
#include "Sensor.h" 
#include "Button.h"
#include "Compass.h"

int startDir, turnCount;

int main(int argc, char **argv) {

	Motor_init();
	Sensor_init();
	Button_init();
	Compass_init();
	
	turnCount = 0;
	
	while(1) {
		int front = (Sensor_getDistance(Sensor_FRONT_LEFT) +
					Sensor_getDistance(Sensor_FRONT_RIGHT)) / 2;
		
		while(front > 20) {
			if(Compass_inRange(startDir, 15, 180))
				Motor_steerLeft(0.9);
			else if(Compass_inRange(startDir, 180, 45))
				Motor_steerRight(0.9);
			else
				Motor_forward();
		}
		
		hugObstacle();
	}
	
	Motor_cleanUp();
	Sensor_cleanUp();
	Button_cleanUp();
}

	
void hugOpstacle() {
		
	while(!(inRange(440, 20) && turnCount == 0)) {
		int right = Sensor_getDistance(Sensor_RIGHT);
		int left = Sensor_getDistance(Sensor_LEFT);
		int front = (Sensor_getDistance(Sensor_FRONT_LEFT) + 
				Sensor_getDistance(Sensor_FRONT_RIGHT)) / 2;
		
		
		if(right < 10)
			Motor_steerLeft(0.9);
		else if(rechts < 30) {
			if(voor > 20)
				Motor_Forward();
			else
				Motor_TurnLeft();
		}
		else if(rechts < 40)
			Motor_steerRight(0.9);	
		else
			Motor_turnRight();
		
		calculateTurnCount();
	}
}

void calculateTurnCount() {
	int oldDir = turnCount * 90;
	if(Compass_inRange(oldDir + 70, oldDir + 110)
		turnCount++;
	else if(Compass_inRange(oldDir + 250, oldDir + 290))
		turnCount--;
}
