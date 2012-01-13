
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
#define DEVICE_NAME "lart"	/* Dev name as it appears in /dev/..   */
#define BUF_LEN 80		/* Max length of the message from the device */

#define MS_TO_NS(x)	(x * 1E6L)

static int Major = 121;		/* Major number assigned to our device driver */


static struct file_operations fops = {
  .write = device_write
};

// Global variables are declared as static, so are global within the file
static ktime_t basetime,lefttime,righttime;
static struct hrtimer base_timer , left_timer , right_timer;
static unsigned long base;

enum hrtimer_restart base_tick( struct hrtimer *timer )
{
  GPCR = ~(base); // CLEAR ALL THE PINS that will not be set :O
  GPSR = base | (1 << PIN_ENGINE_LEFT_ENABLE) | (1 << PIN_ENGINE_RIGHT_ENABLE);

  hrtimer_cancel( &left_timer );
  hrtimer_cancel( &right_timer );

  hrtimer_start( &base_timer, basetime, HRTIMER_REL );
  hrtimer_start( &left_timer, lefttime, HRTIMER_REL );
  hrtimer_start( &right_timer, righttime, HRTIMER_REL );
  
  return HRTIMER_NORESTART;
}


enum hrtimer_restart left_tick( struct hrtimer *timer )
{
  GPCR = (1 << PIN_ENGINE_LEFT_ENABLE);
  return HRTIMER_NORESTART;
}

enum hrtimer_restart right_tick( struct hrtimer *timer )
{
  GPCR = (1 << PIN_ENGINE_RIGHT_ENABLE);
  return HRTIMER_NORESTART;
}

int init_module( void )
{
  
  if(register_chrdev(Major, DEVICE_NAME, &fops) < 0){
    printk(KERN_ALERT "Registering char device failed with %d\n", Major);
    return Major;
  }
  
  // Input/Output register
  GPDR = 0xFFFF;
  // Clear (output) pins
  GPCR = 0xFFFF;

  base = GPSR;

  printk(KERN_INFO "HR Timer module installing\n");

  hrtimer_init( &base_timer, CLOCK_MONOTONIC, HRTIMER_REL );
  hrtimer_init( &left_timer, CLOCK_MONOTONIC, HRTIMER_REL );
  hrtimer_init( &right_timer, CLOCK_MONOTONIC, HRTIMER_REL );

  // bind all timers to functions
  base_timer.function =   (void*)&base_tick;
  left_timer.function =   (void*)&left_tick;
  right_timer.function =  (void*)&right_tick;

  // initialize all the times to reasonable values
  basetime = ktime_set(0, MS_TO_NS(100));
  lefttime = ktime_set(0, MS_TO_NS(10));
  righttime = ktime_set(0, MS_TO_NS(10));

  
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