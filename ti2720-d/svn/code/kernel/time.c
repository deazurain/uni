#include <linux/init.h>
#include <linux/module.h>
#include <asm/hardware.h>
#include <linux/timer.h>

static struct timer_list my_timer;
int ret;
int i;

static void motorAan(void)
{
  GPDR = 0xFFFFFF;
  GPSR = 1 << 4 | 1 << 3 | 1 << 7| 1 << 6; 
  printk("Aan");
  return ;
}

static void motorUit(unsigned long data)
{
  printk("Uit");
  GPSR = 0;
  return ;
}

static int motorSnelheid(int tijdAan)
{
  motorAan();
  setup_timer( &my_timer, motorUit, 0 );
  ret = mod_timer( &my_timer, jiffies + msecs_to_jiffies(tijdAan / 2));
  return 0;
}

static int InitTimer(void)
{
  for(i = 0; i < 1; i ++)
    motorSnelheid(50);
  for(i = 0; i < 1; i ++)
    motorSnelheid(1000);
  return 0;
}



static int init(void)
{
  InitTimer();
  return 0;
}

static void time_exit(void)
{
  ret = del_timer( &my_timer );
  return ;
}

module_init(init);
module_exit(time_exit);

