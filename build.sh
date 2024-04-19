#!/bin/bash

# navigate to Makefile directory
cd source/Makefile

# run Makefile
make

sudo chmod +x kernel_module.o
sudo chmod +x chatbot_driver.py
# run kernel_module.c first to create 'chatbot' device 
# then run chatbot_driver.py 
./kernel_module
python3 chatbot_driver.py