#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#define DEV_NAME "kbuf"

static const int major=63;
static const int minor=0;
struct cdev *my_kbuf;
int chardev_open(struct inode *inode,struct file *filp)
{
  printk( "!!!!!!!OPEN module\n" );
  return -EINVAL;



}
static ssize_t chardev_read( struct file *filp, char *buf, size_t lengthb, loff_t * ofs )
{
     printk(KERN_INFO "Read module\n");
     
     return -EINVAL;
}

static ssize_t chardev_write( struct file *filp, const char *buf, size_t lengthb, loff_t * ofs )
{
      printk( "!!!!!!!!Write module\n" );
      return -EINVAL;
}
static const struct file_operations chardev_fops=
{
  .owner=THIS_MODULE,
  .read=chardev_read,
  .write=chardev_write, 
  .open=chardev_open,
 // .release=chardev_release,   
};
 static int _init_chardev(void)
 {
     dev_t first_node=MKDEV(major,minor);
     printk(KERN_INFO "!!!!!!!!!init new module\n");
     register_chrdev_region(first_node,1,DEV_NAME);
     my_kbuf=cdev_alloc();
     register_chrdev(major,DEV_NAME,&chardev_fops);    
     cdev_init(my_kbuf,&chardev_fops);
     cdev_add(my_kbuf,first_node,minor);
   return 0;
}
static void _exit_chardev(void)
{
    printk(KERN_INFO "!!!!!!!Unload \n"); 
}







module_init(_init_chardev);
module_exit(_exit_chardev);
