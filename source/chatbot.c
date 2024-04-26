#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define DEVICE_NAME "chatbot"
#define BUF_SIZE 256

static int major_number;
static char *chat_response = "Hello! I'm the ChatGPT chatbot kernel module.";

static int device_open(struct inode *inode, struct file *file) {
    return 0; // Always succeed
}

static int device_release(struct inode *inode, struct file *file) {
    return 0; // Always succeed
}

static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset) {
    size_t bytes_to_copy = min(length, strlen(chat_response) + 1); // +1 for null terminator
    if (copy_to_user(buffer, chat_response, bytes_to_copy) != 0)
        return -EFAULT;
    return bytes_to_copy;
}

static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset) {
    // Handle input from user space (not implemented in this example)
    return length; // Return the number of bytes written
}

static struct file_operations file_ops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
};

static int __init chatbot_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &file_ops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "Registered device with major number %d\n", major_number);
    return 0;
}

static void __exit chatbot_exit(void) {
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Unregistered device\n");
}
