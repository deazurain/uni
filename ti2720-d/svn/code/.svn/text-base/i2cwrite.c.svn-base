#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "i2c-dev.h"

int main(){
  int address = 0xE0;
  int file;
  int adapter_nr = 0; /* probably dynamically determined */
  char filename[20];
    
  snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
  file = open(filename, O_RDWR);
  if (file < 0) {
    /* ERROR HANDLING; you can check errno to see what went wrong */
    return 1;
  }

   if (ioctl(file, I2C_SLAVE, address) < 0) {
     /* ERROR HANDLING; you can check errno to see what went wrong */
     exit(1);
   }

  unsigned char reg = 0x00; /* Device register to access */

  unsigned char cmd = 80;

  /* Using I2C Write, equivalent of 
  *      i2c_smbus_write_word_data(file, register, 0x6543) */
  if (i2c_smbus_write_byte_data(file, reg, cmd) < 0) {
    printf("FUUUU");
  }
  return 0;
}


