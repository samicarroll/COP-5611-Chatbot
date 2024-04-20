# Makefile to work with macOS Silicon Architecture

# target and object related to kernel_module.c
TARGET = kernel_module.kext
OBJS = kernel_module.o

# path to Apple SDK needed to develop kernel extension
SDK_PATH ?= /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk


CC = clang
LD = ld

CFLAGS = -Wall -Werror -O2
LDFLAGS = -arch arm64 macosx_version_min 11.0 -lkmod

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)