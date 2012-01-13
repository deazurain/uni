
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/fs.h>
#include <asm/hardware.h>

MODULE_LICENSE("GPL");

int init_module(void);
void cleanup_module(void);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static unsigned long links,rechts,base;

#define SUCCESS 0
#define DEVICE_NAME "lart"	/* Dev name as it appears in /proc/devices   */
#define BUF_LEN 80		/* Max length of the message from the device */

#define MS_TO_NS(x)	(x * 1E6L)

static int Major =121;		/* Major number assigned to our device driver */


static struct file_operations fops = {
	.write = device_write
};

static ktime_t basetime,lefttime,righttime;
static struct hrtimer base_timer , left_timer , right_timer;

enum hrtimer_restart tick( struct hrtimer *timer )
{
        GPSR = base;



	hrtimer_start( &base_timer, basetime, HRTIMER_REL );
	hrtimer_start( &left_timer, lefttime, HRTIMER_REL );
	hrtimer_start( &right_timer, righttime, HRTIMER_REL );
	
	return HRTIMER_NORESTART;
}


enum hrtimer_restart left( struct hrtimer *timer )
{
  GPCR = base & links;
  return HRTIMER_NORESTART;
}

enum hrtimer_restart right( struct hrtimer *timer )
{
  GPCR = base & rechts;
  
  return HRTIMER_NORESTART;
}

int init_module( void )
{
  
  GPDR = 0xFFFF;
  GPCR = 0xFFFF;
  base = GPSR;
  links = 1 << 4| 1<< 3|1<<2;  
  rechts = 1 << 5 | 1 << 6|1<<7;
  
	printk("HR Timer module installing\n");
	hrtimer_init( &base_timer, CLOCK_MONOTONIC, HRTIMER_REL );
	hrtimer_init( &left_timer, CLOCK_MONOTONIC, HRTIMER_REL );
	hrtimer_init( &right_timer, CLOCK_MONOTONIC, HRTIMER_REL );
	base_timer.function = &tick;
	left_timer.function = &left;
	right_timer.function = &right;
	basetime = ktime_set( 0, MS_TO_NS(100L) );
	lefttime = ktime_set( 0, MS_TO_NS(0L) );
	righttime = ktime_set (0,MS_TO_NS(0L));

	if (register_chrdev(Major, DEVICE_NAME, &fops) != 0) {
	  printk(KERN_ALERT "Registering char device failed with %d\n", Major);
	  return Major;
	}
        
	hrtimer_start( &base_timer, basetime, HRTIMER_REL );
	return 0;
	
}

void cleanup_module( void )
{
  GPCR = 0xFFFF;
	int ret;
	ret = hrtimer_cancel( &base_timer );
	unregister_chrdev(Major, DEVICE_NAME);	
	if (ret) 
		printk("The timer was still in use...\n");

	printk("HR Timer module uninstalling\n");

	
	return;
}

static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	unsigned long *ptr = buff;

	//printk("0 =%lu   1 = %lu  2= %lu 3= %lu \n",ptr[0],ptr[1],ptr[2],ptr[3]);

	base = ptr[0];
	basetime = ktime_set( 0, ptr[1] );
	lefttime = ktime_set( 0,ptr[2] );
	righttime = ktime_set (0,ptr[3]);
	
	return -EINVAL;
}
