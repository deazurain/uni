
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>

MODULE_LICENSE("GPL");

#define MS_TO_NS(x)	(x * 1E6L)


static unsigned long hleft =100;
static unsigned long hright = 100;
static unsigned long hbase = 200;
static unsigned long nleft=100;
static unsigned long nright=100;
static unsigned long nbase =200;
static ktime_t basetime,lefttime,righttime;
static struct hrtimer base_timer , left_timer , right_timer;

enum hrtimer_restart tick( struct hrtimer *timer )
{
	
	
	printk( "tick (%ld).\n", jiffies );
	if(hbase != nbase){
		hbase == nbase;
		basetime = ktime_set( 0, MS_TO_NS(hbase) );
	}
	if(hleft != nleft){
		hleft == nleft;
		lefttime = ktime_set( 0, MS_TO_NS(hleft) );
	}
	if(hright != nright){
		hright == nright;
		righttime = ktime_set (0,MS_TO_NS(hright));
	}

	hrtimer_start( &base_timer, basetime, HRTIMER_MODE_REL );
	hrtimer_start( &left_timer, lefttime, HRTIMER_MODE_REL );
	hrtimer_start( &right_timer, righttime, HRTIMER_MODE_REL );
	
	return HRTIMER_NORESTART;
}



enum hrtimer_restart left( struct hrtimer *timer )
{
	printk( "left (%ld).\n", jiffies );
	return HRTIMER_NORESTART;
}

enum hrtimer_restart right( struct hrtimer *timer )
{
	printk( "right (%ld).\n", jiffies );
	return HRTIMER_NORESTART;
}

int init_module( void )
{
	printk("HR Timer module installing\n");
	basetime = ktime_set( 0, MS_TO_NS(hbase) );
	lefttime = ktime_set( 0, MS_TO_NS(hleft) );
	righttime = ktime_set( 0, MS_TO_NS(hright) );
	hrtimer_init( &base_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL );
	hrtimer_init( &left_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL );
	hrtimer_init( &right_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL );
	base_timer.function = &tick;
	left_timer.function = &left;
	right_timer.function = &right;
	printk( "fire in %ldms (%ld)\n", hbase, jiffies );
	hrtimer_start( &base_timer, basetime, HRTIMER_MODE_REL );
	return 0;
	
}

void cleanup_module( void )
{
	int ret;
	ret = hrtimer_cancel( &base_timer );
	if (ret) 
		printk("The timer was still in use...\n");

	printk("HR Timer module uninstalling\n");
	return;
}
