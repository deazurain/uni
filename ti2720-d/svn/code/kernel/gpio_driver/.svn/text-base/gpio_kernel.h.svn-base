/* gpio_kernel.h

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
void InitGPIO(void);
void InitPPC(void);
void CleanupGPIO(void);
void CleanupPPC(void);

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

int GetPPCPin(int whichPin);
unsigned long GetPPCMask(void);

void SetPPCPin(int whichPin);
void ClearPPCPin(int whichPin);
void ModifyPPCPins(unsigned long val, unsigned long mask);

void SetPPCPinDir(int whichPin, int dir);
unsigned long GetPPCPinDirMask(void);
void SetPPCPinDirMask(unsigned long val, unsigned long mask);

