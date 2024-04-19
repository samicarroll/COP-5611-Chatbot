#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

// define device name and IOCTL command
#define DEVICE_NAME "chatbot"
#define IOCTL_CHATGPT_QUERY 0x1000

// function to handle device open operation
static int device_open(struct inode *inode, struct file *file) {
    return 0;  // success
}

// function to handle device release operation
static int device_release(struct inode *inode, struct file *file) {
    return 0;  // success
}

// function to handle device IOCTL operation
static long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
    char buffer[1024];

    switch (cmd) {
        case IOCTL_CHATGPT_QUERY:
            // copy user data from userspace to kernel space
            if (copy_from_user(buffer, (char *)arg, 1024)) {
                return -EFAULT;  // error: unable to copy from user space
            }
            printk(KERN_INFO "Received prompt: %s\n", buffer);

            // copy data from kernel space to userspace
            if (copy_to_user((char *)arg, buffer, 1024)) {
                return -EFAULT;  // error: unable to copy to user space
            }
            return strlen(buffer);  // return length of copied data
        default:
            return -ENOTTY;  // error: unsupported IOCTL command
    }
}

// file operations structure
static struct file_operations fops = {
    .unlocked_ioctl = device_ioctl,  // IOCTL handler
    .open = device_open,             // open handler
    .release = device_release        // release handler
};

// module initialization function
static int __init chatbot_init(void) {
    int ret = register_chrdev(0, DEVICE_NAME, &fops);  // register device
    if (ret < 0) {
        printk(KERN_ALERT "chatbot: failed to register a device\n");
        return ret;  // error: registration failed
    }
    printk(KERN_INFO "chatbot: device registered\n");
    return 0;  // success
}

// function to exit module
static void __exit chatbot_exit(void) {
    unregister_chrdev(0, DEVICE_NAME);  // Unregister device
    printk(KERN_INFO "chatbot: device unregistered\n");
}

// module initialization and exit declaration
module_init(chatbot_init);
module_exit(chatbot_exit);
