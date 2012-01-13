/*
 * Sensor.h
 *
 * Defines functions to read data from the Sensors
 */

#ifndef SENSOR_H
#define SENSOR_H

// standard
int Sensor_init();
int Sensor_cleanup();

// public constants
enum {
  Sensor_LEFT        = 0,
  Sensor_FRONT_LEFT  = 1,
  Sensor_FRONT_RIGHT = 2,
  Sensor_RIGHT       = 3 
};

// methodsz
void Sensor_update();
int Sensor_getDistance(int sensor_id);

#endif
