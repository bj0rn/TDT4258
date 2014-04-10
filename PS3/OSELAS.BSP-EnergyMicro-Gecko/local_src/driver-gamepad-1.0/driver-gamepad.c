/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

/*
 * template_init - function to insert this module into kernel space
 *
 * This is the first of two exported functions to handle inserting this
 * code into a running kernel
 *
 * Returns 0 if successfull, otherwise -1
 */

static int my_probe(struct platform_device *dev){
	printk("Hello world, here is your new module speaking\n");
	return 0;
}


static int my_remove(struct platform_device *dev){
	printk("Leaving\n");
	return 0;
}


static const struct of_device_id my_of_match[] = {
	{.compitable = "tdt4258", }, 
	{},
};

MODULE_DEVICE_TABLE(of, my_of_match);

static struct platform_driver my_driver = {
	.probe = my_probe,
	.remove = my_remove, 
	.driver = {
		.name = "my",
		.owner = THIS_MODULE,
		.of_match_table = my_of_match,
	},
};

platform_driver_register(&my_driver);



/* 
static int __init template_init(void)
{
	printk("Hello World, here is your module speaking or is it ?\n");
	return 0;
}
*/
/*
 * template_cleanup - function to cleanup this module from kernel space
 *
 * This is the second of two exported functions to handle cleanup this
 * code from a running kernel
 */

/* 
static void __exit template_cleanup(void)
{
	 printk("Short life for a small module...\n");
}
*/
//module_init(template_init);
//module_exit(template_cleanup);

//MODULE_DESCRIPTION("Small module, demo only, not very useful.");
//MODULE_LICENSE("GPL");

