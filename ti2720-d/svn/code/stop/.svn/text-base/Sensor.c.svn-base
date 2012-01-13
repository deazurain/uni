/*
 * Sensor.c
 *
 * Defines functions to read data from the Sensors
 */

#include "Sensor.h"

// dependencies
#include <stdio.h>
#include <unistd.h>
#include "HardwareConstants.h"
#include "Median5Filter.h"
#include "i2cio.h"

// globals
int fd = -1;
FILE * logfd;

int snum = 4;
int sorder[] = {1,3,2,3};
int saddr[] = {REG_SENSOR_SL, REG_SENSOR_FL, REG_SENSOR_FR, REG_SENSOR_SR};
int sval[] = {0,0,0,0};
int smed[] = {0,0,0,0};
Median5Filter sfil[4];
int si = 0;

// standard
int Sensor_init() {
  int i;
 
  fd = i2c_InitFile(0);
  logfd = fopen("log", "w");

  for(i = 0; i < snum; i++) {
    Median5Filter_init(&sfil[i]);
  }

  fprintf(logfd, "RL\t\tFL\t\tFR\t\tRR\n");
  fprintf(logfd, "real\tmed\treal\tmed\treal\tmed\treal\tmed\n");
  fflush(logfd);

  return 0;
}

int Sensor_cleanup() {
  return -1; // error
}

// specifique

void startReading(int sensor_address) {
  i2c_BindDevice(fd, sensor_address);
  i2c_WriteByte(fd, REG_SENSOR_COMMAND, 0x50);
}

int waitAndRead(int sensor_address) {
  int val = 0;
  unsigned char res1;
  unsigned char res2;
  unsigned char res;

 // wait for completion
  i2c_BindDevice(fd, sensor_address);
  val = 255;
  while(val == 255) {
    read(fd, &val, 1);
    usleep(5000);
  }
  
  // read sensor
  res1 = i2c_ReadByte(fd, 2);
  res2 = i2c_ReadByte(fd, 3);
  res = (res1 << 8) + res2;

  return res;
}

int Sensor_getFileDescriptor() {
  return fd;
}

void Sensor_update() {

  int v;

  int i = sorder[si];

  startReading(saddr[i]);

  usleep(68000);
  usleep(68000);
  usleep(68000);

  v = waitAndRead(saddr[i]);

  sval[i] = v;

  Median5Filter_addValue(&sfil[i], v);

  smed[i] = Median5Filter_getMedian(&sfil[i]);

  if(si > snum - 2) {
    // full loop
    si = 0;

    /*
    printf("L %d\tFL %d\tFR %d\tR %d\n", 
        smed[0],
        smed[1],
        smed[2],
        smed[3]);
        */

    fprintf(logfd, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        sval[0], smed[0], 
        sval[1], smed[1], 
        sval[2], smed[2], 
        sval[3], smed[3]);
    fflush(logfd);
  }
  else {
    si++;
  }
}
 

int Sensor_getDistance(int sensor_id) {
  if(sensor_id >= snum) return -1;
  return smed[sensor_id];
}

