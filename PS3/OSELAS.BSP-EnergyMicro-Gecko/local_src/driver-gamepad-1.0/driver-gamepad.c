/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>


/*Prototypes*/
static int init_driver();
static void cleanup_driver();
static int open_driver(struct inode *node, struct file *filp);
static int release_driver(struct inode *inode, struct file *filp);
static ssize_t read_driver(struct file *filp, char __user *buff, size_t count, loff_t *offp);
static ssize_t write_driver(struct file *filp, const char __user *buf, size_t count, loff_t *offp);

/*Function pointers*/
//int (*open_driver)(struct inode*, struct file *);
//int (*release_driver)(struct inode *, struct file*);
//ssize_t (*read_driver)(struct file*, char __user *, size_t, loff_t); 
//ssize_t (*write_driver)(struct file*, char __user*, size_t, loff_t);


/*Structures*/
struct cdev driver_cdev;
struct class *cl;
dev_t devno;
int tdt4258_major;
int tdt4258_minor;




static struct file_operations fops = {
	.owner = THIS_MODULE, 
	.read = read_driver,
	.write = write_driver,
	.open = open_driver,
	.release = release_driver
};



/*
 * template_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */

static int __init init_driver(void)
{
	err = alloc_chrdev_region(&devno, 0, 1, "tdt4258");
	
	//int err, devno = MKDEV(tdt4258_major,tdt4258_minor);
	//err = register_chrdev_region(devno, 1, "tdt4258");
	
	cdev_init(&driver_cdev, &fops);  	    //Init the cdev
	driver_cdev.owner = THIS_MODULE;
	//driver_cdev.ops = &fops;
	err = cdev_add(&driver_cdev, devno, 1); //Register to kernel
	

	//Fail nicely
	if(err < 0){
		printk("Error %d", err);
	}else {
		printk("Device added to the kernel sucessfully\n");
	}

	
	cl = class_create(THIS_MODULE, "tdt4258");
	device_create(cl, NULL, devno, NULL, "tdt4258");
	


	
	
	printk("Hello World, here is your module speaking or is it ?\n");
	return 0;
}


/*
 * template_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit cleanup_driver
{
	 printk("Short life for a small module...\n");
}


/*User program opens the driver*/
//static int open_driver(struct inode *node, struct file *filp){

//}

/*User program close the driver*/
//static int release_driver(struct inode *inode, struct file *filp){

//}


/*User program reads from the driver */

//static ssize_t read_driver(struct file *filp, char __user *buff, size_t count, loff_t *offp){

//}


//static ssize_t write_driver(struct file *filp, const char __user *buf, size_t count, loff_t *offp){

//}


module_init(init_driver);
module_exit(cleanup_driver);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");

