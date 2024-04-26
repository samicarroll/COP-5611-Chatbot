#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/kfifo.h>
#include <linux/sched.h>
#include <linux/wait.h>

#define DEVICE_NAME "chatbot"
#define BUF_SIZE 256

static int major_number;
static char response_buffer[BUF_SIZE];
static DECLARE_KFIFO(response_fifo, char, BUF_SIZE);
static DECLARE_WAIT_QUEUE_HEAD(response_wait_queue);
static int response_ready;

static int device_open(struct inode *inode, struct file *file) {
    return 0; // Always succeed
}

static int device_release(struct inode *inode, struct file *file) {
    return 0; // Always succeed
}

static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset) {
    ssize_t bytes_read = 0;

    if (wait_event_interruptible(response_wait_queue, response_ready != 0))
        return -ERESTARTSYS;

    if (kfifo_len(&response_fifo) > 0) {
        if (length > kfifo_len(&response_fifo))
            length = kfifo_len(&response_fifo);

        if (copy_to_user(buffer, response_fifo, length))
            return -EFAULT;

        kfifo_out(&response_fifo, buffer, length);
        bytes_read = length;
    }

    response_ready = 0;

    return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset) {
    char *input = kmalloc(length + 1, GFP_KERNEL);

    if (!input)
        return -ENOMEM;

    if (copy_from_user(input, buffer, length)) {
        kfree(input);
        return -EFAULT;
    }

    input[length] = '\0';

    // Pass input to user-space helper program for API call
    // For simplicity, we just print the input here
    printk(KERN_INFO "Received input: %s\n", input);

    // Simulate API response
    snprintf(response_buffer, BUF_SIZE, "ChatGPT response to: %s", input);
    kfifo_in(&response_fifo, response_buffer, strlen(response_buffer));

    response_ready = 1;
    wake_up_interruptible(&response_wait_queue);

    kfree(input);

    return length;
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

module_init(chatbot_init);
module_exit(chatbot_exit);
