#include <stdio.h>
#include "i2cio.c"
#include "tank_user.h"

int main(int argc, char **argv)
{
  int fd = i2c_InitFile(0);

  if(i2c_BindDevice(fd, SENSOR_FR) < 0) {
    printf("shit");
    return -1;
  }

  while(1) {
    if(i2c_WriteByte(fd, SENSOR_CMDREG, 0x50) < 0) {
      printf("damn");
      return -2;
    }

    sleep(2);

    unsigned char res1 = i2c_ReadByte(fd, 2);
    unsigned char res2 = i2c_ReadByte(fd, 3);

    unsigned short res = (res1 << 8) + res2;

    printf("res: %d\n", res);
  }

  return 0;
}
