# Kernel version
KERNEL_VERSION := $(shell uname -r)

# Compiler and compiler flags
CC := gcc
CFLAGS := -Wall -I/path/to/headers -I/another/path/to/headers

# Kernel source directory
KERNEL_SRC := /lib/modules/$(KERNEL_VERSION)/build

# Module name
MODULE_NAME := chatbot

# Source files
SRC := $(MODULE_NAME).c

# Object files
OBJ := $(MODULE_NAME).o

# Targets
all: $(MODULE_NAME).ko

$(MODULE_NAME).ko: $(OBJ)
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) clean
	rm -f $(MODULE_NAME).ko
