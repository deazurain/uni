#include <stdio.h>
#include "i2cio.h"
#include "tank_user.h"

int main(int argc, char **argv)
{
  int fd = i2c_InitFile(0);
  FILE * fout = fopen("measures.txt", "w");

  if(i2c_BindDevice(fd, SENSOR_COMPASS) < 0) {
    printf("shit");
    return -1;
  }

  int n = 0;
  while(n < 20) {

    /*
    if(i2c_WriteByte(fd, SENSOR_CMDREG, 0x51) < 0) {
      printf("damn");
      return -2;
    }
    */

    sleep(1);

    unsigned char res1 = i2c_ReadByte(fd, 2);
    unsigned char res2 = i2c_ReadByte(fd, 3);

    unsigned short res = (res1 << 8) + res2;

    if(n < 10) {
      printf("meting #0%d: %dcm\n", n, res);
    }
    else {
      printf("meting #%d: %dcm\n", n, res);
    }
    fprintf(fout, "%d\t%d\n", n, res);

    n++;
  }

  return 0;
}
