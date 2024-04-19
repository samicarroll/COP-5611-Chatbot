#!/bin/bash

# already in Makefile directory, run Makefile
make

# run kernel_module.c first to create 'chatbot' device 
# then run chatbot_driver.py 
./kernel_module
python3 chatbot_driver.py