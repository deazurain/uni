
#ifndef GPIO2_H
#define GPIO2_H

#define BIT2MASK(x) (1UL << (x))
#define MS_TO_NS(x)	(x * 1E6L)

void InitGPIO2(void);
void CleanupGPIO2(void);

int GetGPIOPin2(int whichPin);
unsigned long GetGPIOMask2(void);

void SetGPIOPin2(int whichPin);
void SetGPIOMask2(unsigned long mask);
void ClearGPIOPin2(int whichPin);
void ClearGPIOMask2(void);
void ModifyGPIOPins2(unsigned long val, unsigned long mask);

void SetSpeedLeft(unsigned int speed);
void SetSpeedRight(unsigned int speed);
void writetomod();

#endif
