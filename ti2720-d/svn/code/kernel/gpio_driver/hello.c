#include <stdio.h>
#include "user_gpio.h"

int main(int argc, char **argv)
{
	printf("Begin\n");
	InitGPIO();
	//while(GetGPIOPin(8)) {
	//	if(!GetGPIOPin(9)) {
	//		printf("button is pressed\n");
	//	}
	//}
	SetGPIOPinDir(2,1);
	SetGPIOPinDir(3,1);
	SetGPIOPinDir(4,1);
	SetGPIOPinDir(5,1);
	SetGPIOPinDir(6,1);
	SetGPIOPinDir(7,1);
	
	SetGPIOPin(4);
	SetGPIOPin(7);
		
	while (1){
		
		int left = GetGPIOPin(3);
		int right = GetGPIOPin(6);
	
		if(!GetGPIOPin(8)){
			if(left) SetGPIOPin(3);
			else{
				ClearGPIOPin(3);
			}
		}
		if(!GetGPIOPin(9)){
			if(left) SetGPIOPin(6);
			else{
				ClearGPIOPin(6);
			}
		}
		sleep(5);
	}
	CleanupGPIO();
	return 0;
}	
/*
	while(GetGPIOPin(8)) {
	}

	while(GetGPIOPin(9)) {

		SetGPIOPin(4);
		SetGPIOPin(7);
		SetGPIOPin(3);
		SetGPIOPin(6);

	}

	
	ClearGPIOPin(4);
	ClearGPIOPin(7);
	ClearGPIOPin(3);
	ClearGPIOPin(6);
	
	printf("End\n");
	CleanupGPIO();
	return 0;
}*/
