/*
 * Compass.c
 *
 * Defines compass related functions
 */

#include "Compass.h"

// dependencies
#include <stdio.h>
#include "Sensor.h" // uses it's file descriptor
#include "i2cio.h"
#include "HardwareConstants.h"

// globals
int norm_dir = 0;
int direction;

int fd;

// standard
void Compass_init() {
	fd = Sensor_getFileDescriptor();

	if(i2c_BindDevice(fd, REG_COMPASS) < 0) {
		printf("Error in Compass_init");
	}

	Compass_update();
	norm_dir = Compass_getDirection();
}

// update the direction value from the hardware
void Compass_update() {
	i2c_BindDevice(fd, REG_COMPASS);
        unsigned char res1 = i2c_ReadByte(fd, 2);
	unsigned char res2 = i2c_ReadByte(fd, 3);

	direction = (res1 << 8) + res2;
}

// returns the direction in whole degrees
int Compass_getDirection() {
	return direction / 10;
}

int mod360(int n) {
	while(n < 0) n += 360;
	while(n >= 360) n -= 360;
	return n;
}

// returns true if the current direction is within the given bounds, false otherwhise
int Compass_inRange(int lower, int upper) {
	return mod360(Compass_getDirection() - norm_dir - lower) <= mod360(upper - lower);
}

// returns the angle: direction corrected by the normal direction
int Compass_getAngle() {
	return mod360(Compass_getDirection() - norm_dir);
}
