
#define BIT2MASK(x) (1UL << (x))
#define MS_TO_NS(x)	(x * 1E6L)
#define GPSR  data[0]
#define baseloop  data[1]
#define leftloop  data[2]
#define rightloop  data[3]

void InitGPIO(void);
void CleanupGPIO(void);

int GetGPIOPin(int whichPin);
unsigned long GetGPIOMask(void);

void SetGPIOPin(int whichPin);
void SetGPIOMask(unsigned long mask);
void ClearGPIOPin(int whichPin);
void ClearGPIOMask(void);
void ModifyGPIOPins(unsigned long val, unsigned long mask);


void SetSpeedLeft(int speed);
void SetSpeedRight(int speed);
void writetomod();
