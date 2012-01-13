/*  
 *  Prototypes - this would normally go in a .h file
 */
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static int device_mmap(struct file *file, struct vm_area_struct *vma)


#define SUCCESS 0
#define DEVICE_NAME "lart"   /* Dev name as it appears in /proc/devices   */
