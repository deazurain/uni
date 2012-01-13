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
 
#define GPLR (*(volatile unsigned long *) (gpio_map_base))
#define GPDR (*(volatile unsigned long *) (gpio_map_base + 0x04))
#define GPSR (*(volatile unsigned long *) (gpio_map_base + 0x08))
#define GPCR (*(volatile unsigned long *) (gpio_map_base + 0x0C))
 
#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)



static int devmem_fd = -1;
static volatile void *gpio_map_base = NULL;

void InitGPIO(void) {

	assert(gpio_map_base == NULL);
	
    if((devmem_fd == -1) && (devmem_fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    
    /* Map one page */
    gpio_map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, devmem_fd, 0);
    if(gpio_map_base == (void *) -1) FATAL;
    
	
} /* InitGPIO */


void CleanupGPIO(void) {

	if(munmap((void *)gpio_map_base, MAP_SIZE) == -1) FATAL;
    gpio_map_base = NULL;

	if(ppc_map_base == NULL) {
	    close(devmem_fd);
	    devmem_fd = -1;
    }

} /* CleanupGPIO */


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

