#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>

#define DEV_NAME "kbuf"

#define IOCTL_STAT   456

static const int major=63;
static const int minor=0;
struct cdev *my_kbuf;
static const  dev_t first_mode=MKDEV(major,minor);
static char BUF[100];

typedef struct {
                int n_write;
                int n_read;
                int n_open;
                //int n_ioctl;
                int n_release; 
		}STAT30;

STAT30 stat_kbuf;
struct mynet_device {
                         struct net_device *dev;
                         int count_dev;         
                     };
int chrdev_open(struct inode *inode,struct file *filp)
{  
  stat_kbuf.n_open++;
  printk( "!!!!!!!chrdev_open\n" );
  return NULL;
}
int chrdev_release(struct inode *inode,struct file *filp)
{
        printk(KERN_INFO "!!!!!!!chrdev_release \n");
	stat_kbuf.n_release++;
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
netdev_tx_t mydev_netdev_start_xmit(struct sk_buff*skb,struct net_device *dev)
{

  return NET_XMIT_DROP;
}
int mydev_init(struct net_device *dev)
{
	if(register_netdev(dev))
        {
              printk(KERN_INFO "!!!ERROR mydev_netdev_init\n" );
              free_netdev(dev);
              return -EINTR;
        }
	return 0;
}
int mydev_netdev_uninit(struct net_device *dev)
{
          unregister_netdev(dev);
          free_netdev(dev);
          return 0;
}
static void mydev_netdev_init(struct net_device *dev)
{
        struct mydev_netdev *priv = netdev_priv(dev);
        priv->dev = dev;
        ether_setup(dev);

        dev->netdev_ops = &mynet_netdev_ops;
        dev->flags |=IFF_NOARP; 
	printk(KERN_INFO "mydev_netdev_init \n"); 
}

static const struct net_device_ops mynet_netdev_ops=
{
		.ndo_open=      mydev_netdev_open,
                .ndo_stop=      mydev_netdev_stop,  
		.ndo_start_xmit=mydev_netdev_start_xmit,
                .ndo_init=      mydev_netdev_init,
		.ndo_uninit=    mydev_netdev_uninit;
              //.ndo_tx_timeout=mydev_netdev_tx_timeout;
               // .ndo_get_stat=mynet_netdev_get_stats;

};

static void  mydev_netdev_init(struct net_device *dev)
{	
        struct mynet_device *priv=netdev_priv(dev);

	priv->dev = dev;        
        ether_setup(dev);
	dev->netdev_ops=&mynet_netdev_ops;
        dev->flags|=IFF_NOARP;
        //printk(KERN_INFO "mydev_netdev_init \n");

}
static struct net_device *mydev_netdev_create(const char *my_name)
{
   struct net_device *dev;
   printk(KERN_INFO "!!!!! *mydev_netdev_create\n");
   dev=alloc_netdev(sizeof(struct mydev_device),my_name,DEV_NAME_UNKNOWN,mydev_netdev_init);
   if(register_netdev(dev))
   {
         printk(KERN_INFO "Error: *mydev_netdev_create\n");
         free_netdev(dev);
         return NULL;

   }
   return dev;
}
static ssize_t chrdev_read( struct file *filp, char *buf, size_t lengthb, loff_t * ofs )
{
        int nbytes = 0;
	int nbytes_user = 1;
	printk(KERN_INFO "!!!!!chrdev_read \n");     
	stat_kbuf.n_read++;
	nbytes_user = copy_from_user(BUF,buf,lbuf);
	printk(KERN_INFO "nbytes_user=%d BUF=%c \n",nbytes_user,BUF[0]);
	
	if(nbytes_user!= 0)
	{
		printk(KERN_INFO "!!!!Error: read \n");
		return -EINTR;
	}
	nbytes = lbuf - nbytes_user;
        printk(KERN_INFO "chrdev_read: nbytes=%d \n",nbytes);
	*ofs =+ nbytes;
	return nbytes;  
}

long chardev_ioctl(struct *filp, unsigned int cmd, unsigned long arg)
{   
    return 0;
}
static ssize_t chrdev_write( struct file *filp, const char *buf, size_t lengthb, loff_t * ofs )
{
        int nbytes = 0;
	int nbytes_user = 1;
	printk(KERN_INFO "!!!chrdev_write\n");
	stat_kbuf.n_write++;
	nbytes_user = copy_from_user(BUF,buf,lbuf);
	printk(KERN_INFO "!!!chrdev_write:nbytes_user=%d BUF=%c \n",nbytes_user,BUF[0]);
	if(nbytes_user!= 0)
	{
		printk(KERN_INFO "Error: chrdev_write\n");
		return -EINTR;
	}
	nbytes = lbuf - nbytes_user;
        printk(KERN_INFO "!!!chrdev_write:nbytes=%d \n",nbytes);
	*ofs =+ nbytes;
	return nbytes;
}
static const struct file_operations chardev_fops=
{
  .owner=THIS_MODULE,
  .read=chrdev_read,
  .write=chrdev_write, 
  .open=chrdev_open,
  .release=chrdev_release,   
  .unlocked_ioctl=chardev_ioctl,  
};
static int _init_chardev(void)
{      
        dev_t first_node = MKDEV(major,minor);
        printk(KERN_INFO "!!!!!!!!! _init_chardev\n");
	if(register_chrdev_region(first_node,1,"kbuf")<0)
	{
		unregister_chrdev_region(first_node, 1);
		printk(KERN_INFO"Error:_init_chardev\n");
		return -EINTR;
	}

	my_kbuf = cdev_alloc();
        cdev_init(my_kbuf,&chardev_fops);

        if(cdev_add(my_kbuf,first_node,1)<0)
	{
		unregister_chrdev_region(first_node, 1);
		printk(KERN_INFO "!!!Error: cdev_add _init_chardev \n");
		return -EINTR;
	}
        mynet_netdev_init();
        return 0;
}
static void _exit_chardev(void)
{
        dev_t first_node = MKDEV(major,minor);
	printk(KERN_INFO "!!!!!!!_exit_chardev \n");
	cdev_del(my_kbuf);
	unregister_chrdev_region(first_node, 1);
}
module_init(_init_chardev);
module_exit(_exit_chardev);
