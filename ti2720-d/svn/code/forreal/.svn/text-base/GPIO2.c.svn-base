
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "GPIO2.h"
#include "HardwareConstants.h"

FILE *fp;
typedef unsigned long ulong;

ulong data[4];
ulong * const GPSR = data + 0;
ulong * const baseloop = data + 1;
ulong * const leftloop = data + 2;
ulong * const rightloop = data + 3;

ulong prev_data[4];

void InitGPIO2(void) {
  (*GPSR) = (1 << PIN_ENGINE_LEFT_ENABLE) | 
            (1 << PIN_ENGINE_RIGHT_ENABLE);
  (*baseloop) = MS_TO_NS(10);
  (*leftloop) = MS_TO_NS(1);
  (*rightloop) = MS_TO_NS(1);

  fp = fopen("/dev/lart", "wb");
  if (fp == NULL) {
    perror("The following error occurred");
  }
}

void CleanupGPIO2(void) {
  ClearGPIOMask2();
}

unsigned long GetGPIOMask2(void) {
  return (*GPSR);
}


void SetGPIOPin2(int whichPin) {
  (*GPSR) |= (1 << whichPin);
}

void SetGPIOMask2(unsigned long mask) {
  (*GPSR) = mask;
}
 
void ClearGPIOPin2(int whichPin) {
  (*GPSR) &= ~(1 << whichPin);
}

void ClearGPIOMask2(void) {
  (*GPSR) = 0;
}

void ModifyGPIOPins2(unsigned long val, unsigned long mask) {

  if(val & mask)
    SetGPIOMask2(val & mask);
  if(~val & mask)
    SetGPIOMask2(~val & mask);

} 

void SetSpeedLeft(unsigned int frac){
  if(frac > 99) frac = 99;
  if(frac < 1) frac = 1;

  (*leftloop) = ((*baseloop)/100)*frac;
}


void SetSpeedRight(unsigned int frac){
  if(frac > 99) frac = 99;
  if(frac < 1) frac = 1;

  (*rightloop) = ((*baseloop)/100)*frac;
}

void writetomod(){

  //printf("data : %lu %lu %lu %lu\n",data[0],data[1],data[2],data[3]);

  //printf("data:%d\tsize:%d\tcount:%d\tfp%d\n", (int)data, (int)sizeof(unsigned long), (int)4, (int)fp);
  
  if(data[0] == prev_data[0] && data[1] == prev_data[1] && data[2] == prev_data[2] && data[3] == prev_data[3])
    return;
	
	
  fwrite(data, sizeof(unsigned long), 4, fp);
  
  prev_data[0] = data[0];
  prev_data[1] = data[1];
  prev_data[2] = data[2];
  prev_data[3] = data[3];
  fflush(fp);

}
