int main() {
	bool followLeft = true;

	while(1) {
		int fl = Sensor_getDistance(Sensor_FL);
		int fr = Sensor_getDistance(Sensor_FR);
		int f = (fl + fr) / 2;
		boolean gotoWall = f > 10 && f < 100;
		
		if(!(followLeft ^ gotoWall))
			Motor_turnRight();
		else
			Motor_turnLeft();
	}
}
