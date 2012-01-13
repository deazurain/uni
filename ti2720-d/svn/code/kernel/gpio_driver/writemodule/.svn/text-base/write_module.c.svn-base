/*
 *  chardev.c: Creates a read-only char device that says how many times
 *  you've read from the dev file
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>	/* for put_user */

/*  
 *  Prototypes - this would normally go in a .h file
 */
int init_module(void);
void cleanup_module(void);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

const char *crap;
#define SUCCESS 0
#define DEVICE_NAME "lart"	/* Dev name as it appears in /proc/devices   */
#define BUF_LEN 80		/* Max length of the message from the device */

/* 
 * Global variables are declared as static, so are global within the file. 
 */

static int Major =121;		/* Major number assigned to our device driver */


static struct file_operations fops = {
	.write = device_write
};

/*
 * This function is called when the module is loaded
 */
int init_module(void)
{

	if (register_chrdev(Major, DEVICE_NAME, &fops) != 0) {
	  printk(KERN_ALERT "Registering char device failed with %d\n", Major);
	  return Major;
	}
	printk(KERN_INFO "Loading mod %lu\n",jiffies);

	return SUCCESS;
}

/*
 * This function is called when the module is unloaded
 */
void cleanup_module(void)
{
	/* 
	 * Unregister the device 
	 */
	printk(KERN_ALERT "Unloading module %lu \n",jiffies);
	unregister_chrdev(Major, DEVICE_NAME);
}

static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	unsigned long *ptr = buff;

	printk(KERN_ALERT "write. 0 =%lu   1 = %lu  2= %lu \n",
		ptr[0],ptr[1],ptr[2]);
	
	

	
	return -EINVAL;
}
