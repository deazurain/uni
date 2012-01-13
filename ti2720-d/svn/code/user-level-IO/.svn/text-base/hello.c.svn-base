#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "user_gpio.h"
#include "i2c-dev.h"

#define COMPASS 0xC0
#define ADDRESS 0x55
#define FRONTLEFT 0xE0

int main(int argc, char **argv)
{
	printf("Begin\n");

	int fd;
	fd = open("/dev/i2c-0", O_RDWR);

	if(fd == -1) {
		printf("error opening  node: %d", errno);
		return -1;
	}

	if(ioctl(fd, I2C_SLAVE, ADDRESS) < 0) {
		fprintf(stderr, "Failed to set slave address: %m\n");
		return 2;
	}
	if(i2c_smbus_write_byte(fd, (char)COMPASS) < 0)
		fprintf( stderr, "Failed1: %m\n");
	if(i2c_smbus_write_byte(fd, (char)1) < 0)
		fprintf( stderr, "Failed2: %m\n");
	if(i2c_smbus_write_byte(fd, (char)COMPASS && 01111111) < 0)
		fprintf( stderr, "Failed3: %m\n");

	
	int counter = 10;
	while(counter-- > 0) {
		int res = i2c_smbus_read_byte(fd);
		printf("res: %d\n", res);
	}

	printf("End\n");
	return 0;
}

/*
US, front left: 0xE0
US, front right: 0xE2
US, rear left: 0xE4
US, rear right: 0xE6
compass: 0xC0
*/
