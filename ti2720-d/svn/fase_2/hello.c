#include <stdio.h>
#include "user_gpio.h"

int main(int argc, char **argv)
{
	printf("Begin\n");
	InitGPIO();
	while(GetGPIOPin(8)) {
		if(!GetGPIOPin(9)) {
			printf("button is pressed\n");
		}
	}
	printf("End\n");
	CleanupGPIO();
	return 0;
}
