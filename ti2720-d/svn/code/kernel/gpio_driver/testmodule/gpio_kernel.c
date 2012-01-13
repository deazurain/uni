#include <linux/init.h>
#include <linux/module.h>
#include <asm/hardware.h>
#include "gpio_kernel.h"
#include <linux/timer.h>

static struct timer_list my_timer;

void my_timer_callback( unsigned long data )
{
  printk( "my_timer_callback called (%ld).\n", jiffies );

	SetGPIOPin(4);
	SetGPIOPin(7);
	SetGPIOPin(3);
	SetGPIOPin(6);
	SetGPIOPin(8);
	SetGPIOPin(9);
	
 printk("einde callback functie berijkt");
}

unsigned long BIT2MASK(int x)
{
	unsigned long k = 1;
  	return k << x;
}

/*   Copy past van GPIO  */
int GetGPIOPin(int whichPin) {return ((GPLR) >> whichPin) & 0x01;} /* ReadGPIOPin */
unsigned long GetGPIOMask(void) {return GPLR;} /* ReadGPIOMask */
void SetGPIOPin(int whichPin) {	GPSR = 1 << whichPin;} /* SetGPIOPin */
void SetGPIOMask(unsigned long mask) {GPSR = mask;} /* SetGPIOMask */
void ClearGPIOPin(int whichPin) {GPCR = 1 << whichPin;} /* ClearGPIOPin */
void ClearGPIOMask(unsigned long mask) {GPCR = mask;} /* ClearGPIOMask */
void ModifyGPIOPins(unsigned long val, unsigned long mask) {
	if(val & mask)SetGPIOMask(val & mask);
	if(~val & mask)	SetGPIOMask(~val & mask);
} /* ModifyGPIOPins */
void SetGPIOPinDir(int whichPin, int dir) {SetGPIOPinDirMask(dir ? BIT2MASK(whichPin) : 0, BIT2MASK(whichPin));} /* SetGPIOPinDir */
unsigned long GetGPIOPinDirMask(void) {return GPDR;} /* GetGPIOPinDirMask */
void SetGPIOPinDirMask(unsigned long val, unsigned long mask) {GPDR = (GPDR & ~mask) | (val & mask);} /* SetGPIOPinDirMask */

static int init(void)
{
  int ret;
  setup_timer( &my_timer, my_timer_callback, 0 );
  ret = mod_timer( &my_timer, jiffies + msecs_to_jiffies(1000) );
  if (ret) printk("Error in mod_timer\n");



	printk("Loading module");
	printk("mask: %lu \n", BIT2MASK(4));	


	SetGPIOPinDirMask(8405245 ,1); // alle pin directions AAN
	printk("mask: %lu \n", GetGPIOPinDirMask());	

	SetGPIOPin(4);
	SetGPIOPin(7);
	SetGPIOPin(3);
	printk("mask: %lu \n", GetGPIOPinDirMask());
	return 0;
}

static void hello_exit(void)
{
  int ret;

  ret = del_timer( &my_timer );
  if (ret) printk("The timer is still in use...\n");

  return;
}

module_init(init);
module_exit(hello_exit);
