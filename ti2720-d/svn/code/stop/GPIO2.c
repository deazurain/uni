
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "GPIO2.h"

FILE *fp;
typedef unsigned long ulong;

ulong data[4];
ulong * const GPSR = data + 0;
ulong * const baseloop = data + 1;
ulong * const leftloop = data + 2;
ulong * const rightloop = data + 3;

void InitGPIO2(void) {
  (*GPSR) = (1 << 4) | (1<< 7);
  (*baseloop) = MS_TO_NS(100);
  (*leftloop) = MS_TO_NS(1);
  (*rightloop) = MS_TO_NS(1);

  fp = fopen("/dev/lart", "wb");

  if((int)fp < 0) {
    printf("Can't open /dev/lart\n");
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

  fwrite(data, sizeof(ulong), 4, fp);
  fflush(fp);

}
