#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modul koji ispisuje sve procese");
MODULE_AUTHOR("Tihomir");

int modulInit(void){
    struct task_struct *proces;

    printk("Svi procesi su:\n");

    for_each_process(proces){
        printk("naziv = %-20spid = %d", proces->comm, proces->pid);
    }

	return 0;
}

void modulExit(void){}

module_init(modulInit);
module_exit(modulExit);
