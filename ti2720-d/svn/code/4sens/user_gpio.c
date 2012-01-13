/* user_gpio.c

   Simple userspace routines to read and toggle GPIO pins on the SA-11x0.
   Uses mmap(2) on /dev/mem; so the program must have permission to access it.
   WARNING: Be careful not to change pins that the kernel assumes it has 
   exclusive control over !
   
   Created:  20010315, JDB. 
   Modified: 20010328, JDB. Added support for PPC pins.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

   Copyright (C)2001 Jan-Derk Bakker, J.D.Bakker@its.tudelft.nl

*/

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "user_gpio.h"

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


static int devmem_fd = -1;
static volatile void *gpio_map_base = NULL;
static volatile void *ppc_map_base = NULL;
static unsigned long PPFR_copy;


static int PPCCheckAltUsage(unsigned long pinMask);


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
