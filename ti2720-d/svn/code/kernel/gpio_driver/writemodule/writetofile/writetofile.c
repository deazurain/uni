#include <stdio.h>
//#include <stdlib.h>
#include <sys/mman.h>

#include <fcntl.h>
 
#define GPLR (*(volatile unsigned long *) (gpio_map_base))
#define GPDR (*(volatile unsigned long *) (gpio_map_base + 0x04))
#define MAP_SIZE 10
 	
static int lart_fd = -1;
int test = 432;

int main(int argc, char **argv)
{

FILE *fp;
fp=fopen("/dev/lart", "wb");
unsigned long x[3];
x[0] = (unsigned long)atoi(argv[1]);
x[1] = (unsigned long)atoi(argv[2]);
x[2] = (unsigned long)atoi(argv[3]);
fwrite(&x[0], sizeof(long), 3, fp);

  return 0;
}

