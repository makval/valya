#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>


 #include <linux/netdevice.h>
 #include <linux/etherdevice.h>


#define DEV_NAME "kbuf"

#define IOCTL_STAT   456

static const int major=63;
static const int minor=0;
struct cdev *my_kbuf;
static const  dev_t first_mode=MKDEV(major,minor);

static char BUF1[100];
typedef struct {
               //  int N_write,
                // int N_read,
                // int N_open,
               //  int N_ioctl;
		}STAT30;
	



STAT30 stat_kbuf2;
struct mynet_device{
			struct net_device * dev;
			int counter;
			//some 
		    };	

//static netdev_tx_t mynet_netdev_start_xmit(

 int mydev_netdev_uninit(struct net_device *dev)
 {

          unregister_netdev(dev);
          free_netdev(dev);
          return 0;
 }



int mydev_netdev_open(struct net_device *dev)
{
  	return 0;
}
int mydev_netdev_stop(struct net_device *dev)
 {
         return 0;
 }

netdev_tx_t mynet_netdev_start_xmit(struct sk_buff*skb,struct net_device *dev)
{

  return NET_XMIT_DROP;
}
static const struct net_device_ops mynet_netdev_ops=
{
		.ndo_open=mydev_netdev_open,
                .ndo_stop=mydev_netdev_stop,  
		.ndo_start_xmit=mynet_netdev_start_xmit,
//                .ndo_init=mydev_init,
//		.ndo_uninit_mydev_uninit;
 //               .ndo_tx_timeout=mynet_netdev_tx_timeout;
   //             .ndo_get_stat=mynet_netdev_get_stats;

};


static void mynet_device_init(struct net_device *dev)
{	
        struct mynet_device *priv=netdev_priv(dev);

	priv->dev = dev;        
        ether_setup(dev);
	dev->netdev_ops=&mynet_netdev_ops;
        dev->flags|=IFF_NOARP;

}

void mynet_netdev_init(struct net_device *dev)
{
	
}


static struct net_device *mynet_netdev_create(const char *my_name)
{
   struct net_device *dev;
   dev=alloc_netdev(sizeof(struct mynet_device),my_name,NET_NAME_UNKNOWN,mynet_netdev_init);
   if(register_netdev(dev))
   {
         printk(KERN_INFO "Error to register net\n");
         free_netdev(dev);
         return NULL;

   }
   return dev;
}

//static int init my_net(void)
//{
//	struct net_device *dev netdev_create("mynet1");
//}


int chardev_open(struct inode *inode,struct file *filp)
{
  printk( "!!!!!!!OPEN module\n" );
  return NULL;
}

static ssize_t chardev_read( struct file *filp, char *buf, size_t lengthb, loff_t * ofs )
{
    /* int nbytes=copy_to_user(BUF1,buf,lengthb);
     if(nbytes!=0)
      {        
         printk(KERN_INFO  "!!!!!!!!Write buf ERROR\n" );
         return -EINVAL;
       }
    int dnbytes=lengthb-buf;
     printk(KERN_INFO "Read module\n");
    *ofs+=dnbytes;
     return dnbytes; // -EINVAL;
*/
	return 0;
}
long chardev_ioctl(struct *file, unsigned int cmd, unsigned long arg)
/*{   
  //  void *ptr_to_usr=(void*)arg;
    	
//    stat_kbuf.N_ioctl++;
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
 
    }*/
    return 0;
}
static ssize_t chrdev_write( struct file *filp, const char *buf, size_t lengthb, loff_t * ofs )
{
/*
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
*/
	return 0;
}

static const struct file_operations chardev_fops=
{
  .owner=THIS_MODULE,
  .read=chrdev_read,
  .write=chrdev_write, 
  .open=chrdev_open,
  .release=chardev_release,   
  .unlocked_ioctl=chardev_ioctl,  
};

/*static int _init_chardev(void)
 {
     dev_t first_mode=MKDEV(major,minor);
     printk(KERN_INFO "!!!!!!!!!init new module\n");
     register_chrdev_region(first_mode,1,DEV_NAME);
     my_kbuf=cdev_alloc();
    // register_chrdev(major,DEV_NAME,&chardev_fops);    
     if(register_chrdev_region(first_mode,1,"kbuf")<0)
     {
        unregister_chrdev(major,DEV_NAME);  
        printk(KERN_INFO "Error:register_ch ...\n");
        return -EINTR;
     }
//     my_cdev=cdev_alloc();
     cdev_init(my_kbuf,&chardev_fops);
    if(cdev_add(my_kbuf,first_mode,1)<0)
    {
        unregister_chrdev(first_mode,1);  
        printk(KERN_INFO "Error:register_ch ...\n");
        return -EINTR;

    }
    return 0;
 }*/

static int _init_chardev(void)
 {
     dev_t first_mode=MKDEV(major,minor);
     printk(KERN_INFO "!!!!!!!!!init new module\n");
     register_chrdev_region(first_mode,1,DEV_NAME);
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
    if(cdev_add(my_kbuf,first_mode,1)<0)
    {
        unregister_chrdev(first_mode,1);  
        printk(KERN_INFO "Error:register_ch ...\n");
        return -EINTR;

    }

    //if(	mynet_netdev_create("mynet1"))
	//{
	//	fail
	//}

    mynet_netdev_init();
    return 0;
 }
static void _exit_chardev(void)
{
   dev_t first_mode=MKDEV(major,minor);
   cdev_del(my_kbuf);
   unregister_chrdev(first_mode,1);    
   unregister_chrdev(first_mode,1);
     unregister_netdev(dev);
     printk(KERN_INFO "!!!!!!!Unload \n"); 

  //printk(KERN_INFO "!!!!!!!Unload \n"); 
}

 


module_init(_init_chardev);
module_exit(_exit_chardev);
