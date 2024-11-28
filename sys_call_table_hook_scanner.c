#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("marxixing");
MODULE_DESCRIPTION("Detect modified sys_call_table entries.");
MODULE_VERSION("1.0");

static unsigned long *sys_call_table;

static int get_sys_call_table(void) 
{
    sys_call_table = (unsigned long *)kallsyms_lookup_name("sys_call_table");
    if (!sys_call_table) 
    {
        printk(KERN_WARNING "Unable to locate sys_call_table.\n");
        return -1;
    }
    return 0;
}

void print(unsigned char * buf, unsigned int length)
{
    unsigned int i = 0;
    if(buf == NULL)
        return;

    for(i = 0; i < length; i++)
    {
        printk("%02X ", buf[i]);
    }
}

void check_function_owner(unsigned int index, unsigned long long addr)
{
    if(addr == 0)
        return;

    struct module * mod;
    unsigned long long begin = 0;
    unsigned long long end = 0;
    unsigned char mem[32] = {0};

    list_for_each_entry(mod, THIS_MODULE->list.prev, list) 
    {
        begin = (unsigned long long)mod->core_layout.base;
        end   = (unsigned long long)mod->core_layout.base + mod->core_layout.size;

        if (addr >=  begin && addr < end)
        {
            printk("%04X:  %p ", index, addr);
            memcpy(mem, addr, 16);
            print(mem, 16);
            printk("\n");
            printk(KERN_INFO "BEGIN: %p\n", begin);
            printk(KERN_INFO "END:   %p\n", end);
            printk(KERN_INFO "%p belongs to module: %s\n", addr, mod->name);
            return;
        }
    }
}

static void check_critical_syscalls(void)
{
    unsigned int i = 0;
    unsigned long long addr = 0;

    for(i = 0; i < 512; i++)
    {
        addr = (unsigned long long)sys_call_table[i];
        if (addr == 0)
            break;
        check_function_owner(i, addr);
    }
}

static int __init mod_init(void) 
{
    printk(KERN_INFO "sys_call_table hook scanner init.\n");
    if (get_sys_call_table() != 0) 
        return -1;

    unsigned long start_addr, end_addr;
    start_addr = kallsyms_lookup_name("_text");
    end_addr = kallsyms_lookup_name("_end");

    if (!start_addr || !end_addr) 
    {
        printk(KERN_ALERT "Failed to get vmlinux address space.\n");
        return -1;
    }

    printk(KERN_INFO "Kernel start address: %lx\n", start_addr);
    printk(KERN_INFO "Kernel end address:   %lx\n", end_addr);
    printk(KERN_INFO "Kernel size: %lx bytes\n", end_addr - start_addr);
    check_critical_syscalls();

    return 0;
}

static void __exit mod_exit(void) 
{
    printk(KERN_INFO "sys_call_table hook scanner unloaded.\n");
}

module_init(mod_init);
module_exit(mod_exit);

