#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "user_gpio2.c"

#include <termios.h>
#include <unistd.h>



int left ,right = 40;


/* System dependent key codes */
int getkey( ) {
	struct termios oldt,
	newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}






int main(int argc, char **argv) {

InitGPIO();
SetGPIOPin(3);
//SetGPIOPin(4);
SetGPIOPin(6);
//SetGPIOPin(7);
SetSpeedRight(80);
SetSpeedLeft(40);
	return 0;		
}


