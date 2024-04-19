# Makefile to work with Linux machine

# kernel build directory
KERNELDIR := /lib/modules/$(KVERSION)/build

# module name
MODULE_NAME := kernel_module

# source files
SRC := kernel_module.c

# build target
obj-m += $(MODULE_NAME).o

# default target
all:
    $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
    $(MAKE) -C $(KERNELDIR) M=$(PWD) clean
