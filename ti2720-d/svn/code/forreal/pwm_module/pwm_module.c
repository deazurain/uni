/*
 * pwm_module.c
 *
 * Kernel module for setting GPSR and Pulsewidth modulation.
 *
 * PWM on PIN_ENGINE_LEFT_ENABLE and PIN_ENGINE_RIGHT_ENABLE
 * using a duty cycle with period "basetime" and variable ON-periods "lefttime" and "righttime". 
 * All times are in nano seconds because of HR_TIMER 
 *
 * To change values you need to open , write 4 UL's and flush: 
 *
 * EXAMPLE:
 * 
 * ulong data[4];
 * fp = fopen("/dev/lart", "wb");
 * fwrite(data, sizeof(unsigned long), 4, fp);
 * fflush(fp);
 *
 * 
 * The layout of data is: { GPSR , basetime , lefttime , righttime } 
 */




#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/fs.h>
#include <asm/hardware.h>
#include "../HardwareConstants.h"

MODULE_LICENSE("GPL");


int init_module(void);
void cleanup_module(void);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "lart"		// Dev name as it appears in /dev/..   
#define BUF_LEN 80			// Max length of the message from the 
#define MS_TO_NS(x)	(x * 1E6L)

static int Major = 121;			// Major number assigned to our device driver



//function to call when writen to /dev/lart
static struct file_operations fops = {
  .write = device_write
};

// Global variables are declared as static, so are global within the file
static ktime_t basetime,lefttime,righttime;
static struct hrtimer base_timer , left_timer , right_timer;
static unsigned long base;


/*
 * base_tick: Function called when base_timer fires.
 */
enum hrtimer_restart base_tick( struct hrtimer *timer )
{
  // CLEAR ALL THE PINS
  GPCR = 0xffff; 
  GPSR = base | (1 << PIN_ENGINE_LEFT_ENABLE) | (1 << PIN_ENGINE_RIGHT_ENABLE);


  // Cancel timers to make sure no overlap happends or other bugs.
  hrtimer_cancel( &left_timer );
  hrtimer_cancel( &right_timer );

  //start base_timer , left_timer and right_timer
  hrtimer_start( &base_timer, basetime, HRTIMER_REL );
  hrtimer_start( &left_timer, lefttime, HRTIMER_REL );
  hrtimer_start( &right_timer, righttime, HRTIMER_REL );
  
  // HRTIMER_RESTART did not work so instead return HRTIMER_NORESTART
  return HRTIMER_NORESTART;
}

/*
 * left_tick: Function called when left_timer fires.
 * Disable PIN_ENGINE_LEFT_ENABLE by writing to the Clear register 
 */
enum hrtimer_restart left_tick( struct hrtimer *timer )
{
  GPCR = (1 << PIN_ENGINE_LEFT_ENABLE);
  return HRTIMER_NORESTART;
}

/*
 * right_tick: Function called when right_timer fires.
 * Disable PIN_ENGINE_RIGHT_ENABLE by writing to the Clear register 
 */
enum hrtimer_restart right_tick( struct hrtimer *timer )
{
  GPCR = (1 << PIN_ENGINE_RIGHT_ENABLE);
  return HRTIMER_NORESTART;
}


/*
 * init_module: Function called when module is loaded into the kernel 
 */
int init_module( void )
{
  
  //register char driver so it handles the file /dev/DEVICE_NAME with the functions in fops
  if(register_chrdev(Major, DEVICE_NAME, &fops) < 0){
    printk(KERN_ALERT "Registering char device failed with %d\n", Major);
    return Major;
  }
  
  // Set all pins to accept input. 
  GPDR = 0xFFFF;
  // Clear (output) pins
  GPCR = 0xFFFF;
  base = GPSR;

  printk(KERN_INFO "HR Timer module installing\n");

  // Create 3 timers
  hrtimer_init( &base_timer, CLOCK_MONOTONIC, HRTIMER_REL );
  hrtimer_init( &left_timer, CLOCK_MONOTONIC, HRTIMER_REL );
  hrtimer_init( &right_timer, CLOCK_MONOTONIC, HRTIMER_REL );

  // Bind all timers to functions
  base_timer.function =   (void*)&base_tick;
  left_timer.function =   (void*)&left_tick;
  right_timer.function =  (void*)&right_tick;

  // Initialize all the times to reasonable values
  basetime = ktime_set(0, MS_TO_NS(100));
  lefttime = ktime_set(0, MS_TO_NS(40));
  righttime = ktime_set(0, MS_TO_NS(40));

  
  hrtimer_start( &base_timer, basetime, HRTIMER_REL );
  return 0;
  
}

void cleanup_module( void )
{
  // Clear all registers
  GPCR = 0xFFFF;

  // try to cancel all the timers
  if(hrtimer_cancel( &base_timer ))
      printk("/* KERNEL base_timer was still in use...*/\n");
  if(hrtimer_cancel( &left_timer ));
      printk("/* KERNEL left_timer was still in use...*/\n");
  if(hrtimer_cancel( &right_timer));
      printk("/* KERNEL right_timer was still in use...*/\n");

  unregister_chrdev(Major, DEVICE_NAME);	
  printk("/* KERNEL HR Timer module uninstalling...*/\n");

  return;
}

static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
  // longs are passed as arguments to ktime_set instead of chars
  // Const to make sure we don't change the data
  const unsigned long * ptr = (const unsigned long *) buff;
  base = ptr[0];
  basetime  = ktime_set( 0, ptr[1] );
  lefttime  = ktime_set( 0, ptr[2] );
  righttime = ktime_set( 0, ptr[3]);
  
  // by convention 
  return len;
}
