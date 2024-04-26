# COP-5611-Chatbot: Final Project

## System Requirements
*Operating System*

This project requires a **Linux Operating System**. Because my host machine has an arm64 architecture with macOS, I chose to run the project on a VM (Parallels). 

I ran into many issues trying to find a VM and iso image that worked with my host machine. Due to prior knowledge, I tried to use VirtualBox with a Fedora 32 bit OS. I was unsure if this would work with the program or my hardware, but it was an OS and VM I was comfortable using. However, the arm64 iso image provided on the Fedora website did not work with VirtualBox. I believe the problem was with VirtualBox, not the iso, as this issue occured with multiple operating systems, and the iso's worked with other VMs. 

Overall, the VM I chose was Parallels running a Fedora iso image for arm64 architecture. 

*Programming Languages*

Ensure the following Programming languages and tools are installed on the Target Machine:
1. Python3
2. C & GCC

## Build The Project
Before building the project, the source code must be updated with your OpenAI API Key. Because this API key is unqiue to your OpenAI account, it must be removed to be published to GitHub. 

Your API key can be updated in the following source file:
`source/chatbot_driver.py`: line 9

```
# TODO: ADD OPENAI API KEY BEFORE RUNNING build.sh!
OPENAI_API_KEY =
``` 

Once you have updated the API key, run the build script `build.sh` in the terminal using the following command: `./build.sh`

The build script will perform the following operations:
1. navigates to the Makefile directory 
    - `cd source/Makefile`
2. performs the `make` command to build the Makefile
3. runs the executable that is developed by the Makefile and runs the chatbot_driver Python script
    - `./kernel_module`
    - `python3 chatbot_driver.py`


## Development Issues
1. *Developing in Linux on macOS*
    - My prior knowledge working with Linux on macOS is little/none. In the past, I have worked briefly in Linux on Mac as they have similar operating systems. 

## Future Implementations

Ideally, I would have liked to run this project on MacOS, however, this would've required the development of a kernel extension (kext). A kext is risky to the OS and not recommended by Apple support. Per the Apple support website: 
> "In macOS 11 or later, if third-party kernel extensions (kexts) are enabled, they can’t be loaded into the kernel on demand. They require the user’s approval and restarting of the macOS to load the changes into the kernel, and they also require that the secure boot be configured to Reduced Security on a Mac with Apple silicon."
[Apple Support](https://support.apple.com/guide/deployment/system-and-kernel-extensions-in-macos-depa5fb8376f/web)
