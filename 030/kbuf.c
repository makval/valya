#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
//#include <linux/ioctl.h>
#include <linux/uaccess.h>
#define DEV_NAME "kbuf"

#define IOCTL_STAT   456

static const int major=63;
static const int minor=0;
struct cdev *my_kbuf;
//static const dev_t first_node=MKDEV(major,minor);
static char BUF1[100];
typedef struct {
                 int N_write,
                 int N_read,
                 int N_open,
                 int N_ioctl;
		}STAT30;
	


STAT30 stat_kbuf;
long chardev_ioctl(struct *file, unsigned int cmd, unsigned long arg)
{   
    void *ptr_to_usr=(void*)arg;
    	
    stat_kbuf.N_ioctl++;
    printk( "!!!!!!!chardev_ioctl\n" );
    switch(cmd)
    {
      case IOCTL_STAT:
        if(copy_to_user(ptr_to_user,&stat_kbuf,sizeof(stat_kbuf))
          {
              printk(KERN_INFO  "!!!!!!!STAT\n" );

          } 
		
      	break;
      default: printk(KERN_INFO  "!!!!!!!default_ioctl\n" );		
	break;
 
    }
    return 0;
}


int chardev_open(struct inode *inode,struct file *filp)
{
  printk( "!!!!!!!OPEN module\n" );
  return -EINVAL;

}
static ssize_t chardev_read( struct file *filp, char *buf, size_t lengthb, loff_t * ofs )
{
     int nbytes=copy_to_user(BUF1,buf,lengthb);
     if(nbytes!=0)
      {        
         printk(KERN_INFO  "!!!!!!!!Write buf ERROR\n" );
         return -EINVAL;
       }
    int dnbytes=lengthb-buf;
     printk(KERN_INFO "Read module\n");
    *ofs+=dnbytes;
     return dnbytes; // -EINVAL;
}
static ssize_t chrdev_write( struct file *filp, const char *buf, size_t lengthb, loff_t * ofs )
{
     int nbytes=copy_from_user(BUF1,lengthb);
      printk(KERN_INFO  "!!!!!!!!Write module\n" );
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
  .release=chardev_release,   
  .unlocked_ioctl=chardev_ioctl,  
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
