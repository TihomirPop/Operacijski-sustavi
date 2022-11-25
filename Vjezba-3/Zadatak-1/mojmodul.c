#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modul koji ispisuje vrijeme tokom init i exit");
MODULE_AUTHOR("Tihomir");

unsigned long sekundeModula;

int modulInit(void){
	unsigned long bootJiffies = jiffies - (4294967295 - (300 * HZ));
	sekundeModula = jiffies;
	printk(KERN_INFO "mojModulInit - jiffies: %lu\tsekunde: %lu\tbootJiffies: %lu\tbootSekunde: %lu\n", jiffies, jiffies/HZ, bootJiffies, bootJiffies/HZ);
	return 0;
}

void modulExit(void){
	unsigned long bootJiffies = jiffies - (4294967295 - (300 * HZ));
	sekundeModula = (jiffies - sekundeModula)/HZ;
	printk(KERN_INFO "mojModulExit - jiffies: %lu\tsekunde: %lu\tbootJiffies: %lu\tbootSekunde: %lu\ttrajanjeModula: %lu\n", jiffies, jiffies/HZ, bootJiffies, bootJiffies/HZ, sekundeModula);
}

module_init(modulInit);
module_exit(modulExit);
