#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#define DEV_NAME "kbuf"

static const int major=63;
static const int minor=0;
struct cdev *my_kbuf;
//static const dev_t first_node=MKDEV(major,minor);
static char BUF1[100];

int chardev_open(struct inode *inode,struct file *filp)
{
  printk( "!!!!!!!OPEN module\n" );
  return -EINVAL;



}
static ssize_t chardev_read( struct file *filp, char *buf, size_t lengthb, loff_t * ofs )
{

     int nbytes=copy_to_user(BUF1,lengthb);
     if(nbytes!=0)
      {
         
         printk( "!!!!!!!!Write buf ERROR\n" );
         return -EINVAL;
       }

     printk(KERN_INFO "Read module\n");
    *ofs+=nbytes;
     return nbytes; // -EINVAL;
}

static ssize_t chrdev_write( struct file *filp, const char *buf, size_t lengthb, loff_t * ofs )
{

     int nbytes=copy_from_user(BUF1,lengthb);
      printk( "!!!!!!!!Write module\n" );
     //  return -EINVAL;

     if(nbytes!=0)
     {
     
        printk( "!!!!!!!!Write buf ERROR\n" );
        return -EINVAL;
      } 
      *ofs+=nbytes;

      // printk( "!!!!!!!!Write module\n" );

      return nbytes; // -EINVAL;
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
    // register_chrdev(major,DEV_NAME,&chardev_fops);    
     if(register_chrdev_region(first_mode,1,"kbuf")<0)
     {
        unregister_chrdev(first_mode,1);  
        printk(KERN_INFO "Error:register_ch ...\n");
        return -EINTR;
     }
     my_cdev=cdev_alloc();
     cdev_init(my_kbuf,&chardev_fops);
    if(cdev_add(my_kbuf,first_node,1)<0)
    {
        unregister_chrdev(first_mode,1);  
        printk(KERN_INFO "Error:register_ch ...\n");
        return -EINTR;

    }
    return 0;
 }
static void _exit_chardev(void)
{
   dev_t first_node=MKDEV(major,minor);
   cdev_del(my_kbuf);
   unregister_chrdev(first_mode,1);    
   printk(KERN_INFO "!!!!!!!Unload \n"); 
}



module_init(_init_chardev);
module_exit(_exit_chardev);
