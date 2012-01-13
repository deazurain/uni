#include "i2cio.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "i2c-dev.h"
#include "tank_user.h"

int i2c_InitFile(int adapter) {
  char filename[20];
  snprintf(filename, 19, "/dev/i2c-%d", adapter);
  int fd = open(filename, O_RDWR);
  return fd;
}

int i2c_BindDevice(int fd, int addr) {
  int r = ioctl(fd, I2C_SLAVE, addr);
  return r;
}

int i2c_WriteByte(int fd, int reg, unsigned char cmd) {
  return i2c_smbus_write_byte_data(fd, reg, cmd);
  unsigned char _reg = reg;
  write(fd, &_reg, 1);
  return write(fd, &cmd, 1);
}

unsigned char i2c_ReadByte(int fd, int reg) {
  return i2c_smbus_read_byte_data(fd, reg);
  unsigned char ret, _reg = reg;
  write(fd, &_reg, 1);
  read(fd, &ret, 1);
  return ret;
}

void i2c_CleanupFile(int fd) {
  close(fd);
}

