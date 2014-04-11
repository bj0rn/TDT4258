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
#include <linux/ioport.h>
#include <asm/io.h>
#include <linux/uaccess.h>

#include "efm32gg.h"

#define DRIVER "gamepad"
#define BUFFER_SIZE 4 //In bytes


/*Prototypes*/
//static int init_driver();
//static void cleanup_driver();
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
struct resource *resource;






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
	int err = alloc_chrdev_region(&devno, 0, 1, DRIVER);
	
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

	
	cl = class_create(THIS_MODULE, DRIVER);
	device_create(cl, NULL, devno, NULL, DRIVER);
	
	//Request memory
	resource = request_mem_region(GPIO_PC_BASE,32, DRIVER);
	
	if(resource != NULL)
		printk("Works!");	
	
	iowrite32(0x33333333, GPIO_PC_MODEL);
	iowrite32(0xff, GPIO_PC_DOUT);
	
	
	printk("Hello World, here is your module speaking or is it ?\n");
	return 0;
}


/*
 * template_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

static void __exit cleanup_driver()
{
	 printk("Short life for a small module...\n");
}


/*User program opens the driver*/
static int open_driver(struct inode *node, struct file *filp){
	printk("The gamepad is ready to go\n");

	return 0;
}

/*User program close the driver*/
static int release_driver(struct inode *inode, struct file *filp){
	printk("Finished with the driver\n");
	return 0;
}


/*User program reads from the driver */

static ssize_t read_driver(struct file *filp, char __user *buff, size_t count, loff_t *offp){
	//int maxbytes; //Maximum bytes that can be read from
	//int bytes_to_read;	//Gives the number of bytes to read
	//int bytes_read;     //Number of bytes actually read
	//unsigned int data;
	
	//maxbytes = BUFFER_SIZE - *offp;

	//if(maxbytes > count){
	//	bytes_to_read = count;
	//}else{
	//	bytes_to_read = maxbytes;
	//}

	//if(bytes_to_read == 0){
	//	printk("REached end of the device\n");
	//}

	//Read data from buttons
	
	uint32_t data = ioread32(GPIO_PC_DIN);
	copy_to_user(buff, &data, 1);
	
	return 1;

}


static ssize_t write_driver(struct file *filp, const char __user *buf, size_t count, loff_t *offp){
	return 0;
}


module_init(init_driver);
module_exit(cleanup_driver);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");

