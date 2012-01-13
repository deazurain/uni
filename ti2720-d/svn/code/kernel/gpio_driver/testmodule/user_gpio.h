/* user_gpio.h

    External interface for user_gpio.c

    Created: 20010315, JDB.

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

#ifndef __USER_GPIO__
#define __USER_GPIO__

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


void InitGPIO(void);
void CleanupGPIO(void);

int GetGPIOPin(int whichPin);
unsigned long GetGPIOMask(void);

void SetGPIOPin(int whichPin);
void SetGPIOMask(unsigned long mask);
void ClearGPIOPin(int whichPin);
void ClearGPIOMask(unsigned long mask);
void ModifyGPIOPins(unsigned long val, unsigned long mask);

void SetGPIOPinDir(int whichPin, int dir);
unsigned long GetGPIOPinDirMask(void);
void SetGPIOPinDirMask(unsigned long val, unsigned long mask);

#endif
