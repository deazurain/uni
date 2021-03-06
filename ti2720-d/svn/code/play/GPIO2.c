
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "GPIO2.h"

FILE *fp;
unsigned long data[4];


void InitGPIO(void) {
GPSR = 0x0000;
baseloop = MS_TO_NS(100);
leftloop = MS_TO_NS(1);
rightloop = MS_TO_NS(1);

if(fp < 0)
	printf("Could not open /dev/lart");
    	
} /* InitGPIO */


void CleanupGPIO(void) {
	ClearGPIOMask();
} /* CleanupGPIO */



unsigned long GetGPIOMask(void) {
	return GPSR;

} /* ReadGPIOMask */


void SetGPIOPin(int whichPin) {
	GPSR = GPSR | 1 << whichPin;
	writetomod();
} /* SetGPIOPin */


void SetGPIOMask(unsigned long mask) {
	GPSR = mask;
	writetomod();
} /* SetGPIOMask */

 
void ClearGPIOPin(int whichPin) {
	GPSR = GPSR & ~(1 << whichPin);
} /* ClearGPIOPin */


void ClearGPIOMask(void) {
	GPSR = 0x0000;
	writetomod();
} /* ClearGPIOMask */


void ModifyGPIOPins(unsigned long val, unsigned long mask) {

	if(val & mask)
		SetGPIOMask(val & mask);
	if(~val & mask)
		SetGPIOMask(~val & mask);

} /* ModifyGPIOPins */

void SetSpeedLeft(int speed){
	if (speed > 100)
		speed=100;
	if (speed < 0)
		speed=0;
	leftloop = MS_TO_NS(speed);
	writetomod();
}


void SetSpeedRight(int speed){
	if (speed > 100)
		speed=100;
	if (speed < 0)
		speed=0;
	rightloop = MS_TO_NS(speed);
	writetomod();
}


void writetomod(){

printf("data : %lu %lu %lu %lu\n",data[0],data[1],data[2],data[3]);

fp=fopen("/dev/lart", "wb");
fwrite(&data[0], sizeof(long), 4, fp);
fclose(fp);


}
