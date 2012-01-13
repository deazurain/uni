#ifndef I2CIO_H
#define I2CIO_H


int i2c_InitFile(int adapter);

int i2c_BindDevice(int fd, int addr);

int i2c_WriteByte(int fd, int reg, unsigned char cmd);

unsigned char i2c_ReadByte(int fd, int reg);

void i2c_CleanupFile(int fd);
#endif
