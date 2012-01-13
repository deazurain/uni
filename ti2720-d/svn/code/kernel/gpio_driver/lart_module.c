/*
 *  chardev.c: Creates a read-only char device that says how many times
 *  you've read from the dev file
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>



/*  
 *  Prototypes - this would normally go in a .h file
 */
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static int device_mmap(struct file *, struct vm_area_struct *); 

#define SUCCESS 0
#define DEVICE_NAME "chardev"	/* Dev name as it appears in /proc/devices   */
#define BUF_LEN 80		/* Max length of the message from the device */



/* 
 * Global variables are declared as static, so are global within the file. 
 */

static int Major=121;               /* Major number assigned to our device driver */
static int Device_Open = 0;     /* Is device open?  
                                 * Used to prevent multiple access to device */


static struct file_operations fops = {
      
        .open = device_open,
        .release = device_release,
  	.mmap = device_mmap
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
        printk(KERN_INFO "Run setup.sh.\n");

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
        int ret = unregister_chrdev(Major, DEVICE_NAME);
        if (ret < 0)
                printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);
}


/* 
 * Called when a process tries to open the device file, like
 * "cat /dev/mycharfile"
 */
static int device_open(struct inode *inode, struct file *file)
{

        if (Device_Open)
                return -EBUSY;

        Device_Open++;

        try_module_get(THIS_MODULE);

        return SUCCESS;
}

/* 
 * Called when a process closes the device file.
 */
static int device_release(struct inode *inode, struct file *file)
{
        Device_Open--;          /* We're now ready for our next caller */

        /* 
         * Decrement the usage count, or else once you opened the file, you'll
         * never get get rid of the module. 
         */
        module_put(THIS_MODULE);

        return 0;
}

/* 
 * Called when a process, calls mmap.
 */
 
 static int device_mmap(struct file *file, struct vm_area_struct *vma)
 {
 
 if (remap_pfn_range(vma, //user vma to map to 
					vma->vm_start, //target user address to start at 
					0x90040000,//physical address of kernel memory 
					0x10,//size of map area 
					vma->vm_page_prot))//page protection flags for this mapping 
        return -EAGAIN;

    //vma->vm_ops = &fops;
    return 0;


 }
