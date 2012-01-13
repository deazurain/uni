#include <stdio.h>
#include <unistd.h>
#include "Sensor.h"

int main(int argc, char **argv) {

  Sensor_init();

  while(1) {
    Sensor_update();
    printf("L:\t%d\tFL:\t%d\tFR:\t%d\tR:\t%d\n",
      Sensor_getDistance(Sensor_LEFT),
      Sensor_getDistance(Sensor_FRONT_LEFT),
      Sensor_getDistance(Sensor_FRONT_RIGHT),
      Sensor_getDistance(Sensor_RIGHT));
  }

  return 0;
}


