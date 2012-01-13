/*                                                     
 * $Id: hello.c,v 1.5 2004/10/26 03:32:21 corbet Exp $ 
 */                                                    
#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

extern int errno;

#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
  __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)
 
#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

#define GPIO_BASE 0x90040000
#define GPLR (*(volatile unsigned long *) (gpio_map_base))
#define GPDR (*(volatile unsigned long *) (gpio_map_base + 0x04))
#define GPSR (*(volatile unsigned long *) (gpio_map_base + 0x08))
#define GPCR (*(volatile unsigned long *) (gpio_map_base + 0x0C))

#define PPC_BASE 0x90060000
#define PPDR (*(volatile unsigned long *) (ppc_map_base))
#define PPSR (*(volatile unsigned long *) (ppc_map_base + 0x04))
#define PPFR (*(volatile unsigned long *) (ppc_map_base + 0x10))

#define BIT_LDD0   0
#define BIT_LDD1   1
#define BIT_LDD2   2
#define BIT_LDD3   3
#define BIT_LDD4   4
#define BIT_LDD5   5
#define BIT_LDD6   6
#define BIT_LDD7   7
#define BIT_LPCLK  8
#define BIT_LLCLK  9
#define BIT_LFCLK 10
#define BIT_LBIAS 11
#define BIT_TXD1  12
#define BIT_RXD1  13
#define BIT_TXD2  14
#define BIT_RXD2  15
#define BIT_TXD3  16
#define BIT_RXD3  17
#define BIT_TXD4  18
#define BIT_RXD4  19
#define BIT_SCLK  20
#define BIT_SFRM  21

#define BIT2MASK(x) (1UL << (x))

#define PINDIR_INPUT  0
#define PINDIR_OUTPUT 1

#define LCD_MASK  0x000FFF
#define SP1T_MASK 0x001000
#define SP1R_MASK 0x002000
#define SP2T_MASK 0x004000
#define SP2R_MASK 0x008000
#define SP3T_MASK 0x010000
#define SP3R_MASK 0x020000
#define SP4_MASK  0x3C0000



static int devmem_fd = -1;
static volatile void *gpio_map_base = NULL;
static volatile void *ppc_map_base = NULL;
static unsigned long PPFR_copy;



static int init(void)
{
	printk(KERN_ALERT "Modlue starting.\n");
	InitGPIO();
	InitPPC();
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Module stopping.\n");
	CleanupGPIO();
	CleanupPPC();
}
void InitGPIO(void) {

	assert(gpio_map_base == NULL);
	
    if((devmem_fd == -1) && (devmem_fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    
    /* Map one page */
    gpio_map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, devmem_fd, GPIO_BASE);
    if(gpio_map_base == (void *) -1) FATAL;
    
	
} /* InitGPIO */


void InitPPC(void) {
/* Initialize the Peripheral Pin Controller pins as GPIO pins */

	assert(ppc_map_base == NULL);

    if((devmem_fd == -1) && (devmem_fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;

    /* Map one page */
    ppc_map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, devmem_fd, PPC_BASE);
    if(ppc_map_base == (void *) -1) FATAL;
    
    PPFR_copy = PPFR;
    
} /* InitPPC */


void CleanupGPIO(void) {

	if(munmap((void *)gpio_map_base, MAP_SIZE) == -1) FATAL;
    gpio_map_base = NULL;

	if(ppc_map_base == NULL) {
	    close(devmem_fd);
	    devmem_fd = -1;
    }

} /* CleanupGPIO */


void CleanupPPC(void) {

	if(munmap((void *)ppc_map_base, MAP_SIZE) == -1) FATAL;
    ppc_map_base = NULL;

	if(gpio_map_base == NULL) {
	    close(devmem_fd);
	    devmem_fd = -1;
    }

} /* CleanupPPC */


int GetGPIOPin(int whichPin) {

	assert(gpio_map_base != NULL);
	return ((GPLR) >> whichPin) & 0x01;

} /* ReadGPIOPin */


unsigned long GetGPIOMask(void) {

	assert(gpio_map_base != NULL);
	return GPLR;

} /* ReadGPIOMask */


void SetGPIOPin(int whichPin) {

	assert(gpio_map_base != NULL);
	GPSR = 1 << whichPin;
	
} /* SetGPIOPin */


void SetGPIOMask(unsigned long mask) {

	assert(gpio_map_base != NULL);
	GPSR = mask;
	
} /* SetGPIOMask */


void ClearGPIOPin(int whichPin) {

	assert(gpio_map_base != NULL);
	GPCR = 1 << whichPin;
	
} /* ClearGPIOPin */


void ClearGPIOMask(unsigned long mask) {

	assert(gpio_map_base != NULL);
	GPCR = mask;
	
} /* ClearGPIOMask */


void ModifyGPIOPins(unsigned long val, unsigned long mask) {

	if(val & mask)
		SetGPIOMask(val & mask);
	if(~val & mask)
		SetGPIOMask(~val & mask);

} /* ModifyGPIOPins */


void SetGPIOPinDir(int whichPin, int dir) {
/* Sets the direction of GPIO pins. As described in the manual,
   dir == 0 is input */
   
	SetGPIOPinDirMask(dir ? BIT2MASK(whichPin) : 0, BIT2MASK(whichPin));
		
} /* SetGPIOPinDir */


unsigned long GetGPIOPinDirMask(void) {

	return GPDR;
	
} /* GetGPIOPinDirMask */


void SetGPIOPinDirMask(unsigned long val, unsigned long mask) {

	assert(gpio_map_base != NULL);

	GPDR = (GPDR & ~mask) | (val & mask);
	
} /* SetGPIOPinDirMask */


int GetPPCPin(int whichPin) {

	assert(ppc_map_base != NULL);
	
	return ((PPSR) >> whichPin) & 0x01;

} /* ReadPPCPin */


unsigned long GetPPCMask(void) {

	assert(ppc_map_base != NULL);
	
	return PPSR;

} /* ReadPPCMask */


void ModifyPPCPins(unsigned long val, unsigned long mask) {
/* Change the pins indicated in mask to the value in val */

	assert(ppc_map_base != NULL);

	/* Check if we own all the pins in mask */
	assert(PPCCheckAltUsage(mask));
		
	PPSR = (PPSR & ~mask) | (val & mask);
	
} /* ModifyPPCPins */


void SetPPCPin(int whichPin) {

	ModifyPPCPins(BIT2MASK(whichPin), BIT2MASK(whichPin));
	
} /* SetPPCPin */


void ClearPPCPin(int whichPin) {

	ModifyPPCPins(BIT2MASK(0), BIT2MASK(whichPin));
	
} /* ClearPPCPin */


void SetPPCPinDir(int whichPin, int dir) {
/* Sets the direction of PPC pins. As described in the manual,
   dir == 0 is input */
   
	SetPPCPinDirMask(dir ? BIT2MASK(whichPin) : 0, BIT2MASK(whichPin));
		
} /* SetPPCPinDir */


unsigned long GetPPCPinDirMask(void) {

	return PPDR;
	
} /* GetPPCPinDirMask */


void SetPPCPinDirMask(unsigned long val, unsigned long mask) {

	assert(ppc_map_base != NULL);

	/* Check if we own all the pins in mask */
	assert(PPCCheckAltUsage(mask));
	
	PPDR = (PPDR & ~mask) | (val & mask);
	
} /* SetPPCPinDirMask */


static int PPCCheckAltUsage(unsigned long pinMask) {
/* Given a bitmask of PPC pins the user wants to modify, see if any are
   used for their primary function (ie the kernel). Meant to be used in an assert(), so a
   return value of 0 == a conflict */

	int result = 1;

	if((pinMask & LCD_MASK) && ((PPFR_copy & LCD_MASK) == 0)) result = 0;
	if((pinMask & SP1T_MASK) && ((PPFR_copy & SP1T_MASK) == 0)) result = 0;
	if((pinMask & SP1R_MASK) && ((PPFR_copy & SP1R_MASK) == 0)) result = 0;
	if((pinMask & SP2T_MASK) && ((PPFR_copy & SP2T_MASK) == 0)) result = 0;
	if((pinMask & SP2R_MASK) && ((PPFR_copy & SP2R_MASK) == 0)) result = 0;
	if((pinMask & SP3T_MASK) && ((PPFR_copy & SP3T_MASK) == 0)) result = 0;
	if((pinMask & SP3R_MASK) && ((PPFR_copy & SP3R_MASK) == 0)) result = 0;
	if((pinMask & SP4_MASK) && ((PPFR_copy & SP4_MASK) == 0)) result = 0;

	return result;
	
} /* PPCCheckAltUsage */


module_init(hello_init);
module_exit(hello_exit);
