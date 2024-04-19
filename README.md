# COP-5611-Chatbot: Final Project

## System Requirements
*Operating System*
This project requires a **Linux Operating System**. Ideally, I would run this project on MacOS, however, this would've required the development of a kernel extension (kext). A kext is risky to the OS and not recommended by Apple support. Per the Apple support website: 
> "In macOS 11 or later, if third-party kernel extensions (kexts) are enabled, they can’t be loaded into the kernel on demand. They require the user’s approval and restarting of the macOS to load the changes into the kernel, and they also require that the secure boot be configured to Reduced Security on a Mac with Apple silicon."
[Apple Support](https://support.apple.com/guide/deployment/system-and-kernel-extensions-in-macos-depa5fb8376f/web)

*Programming Languages*
Ensure the following Programming languages are installed on the Target Machine:
1. Python3
2. C & GCC


## Build The Project
Before building the project, the source code must be updated with your OpenAI API Key. Because this API key is unqiue to your OpenAI account, it must be removed to be published to GitHub. 

Your API key can be updated in the following source file:
`source/chatbot_driver.py` - line 9

```
# TODO: ADD OPENAI API KEY BEFORE RUNNING build.sh!
# OPENAI_API_KEY =
``` 

Once you have updated the API key, run the build script `build.sh` in the terminal using the following command: `./build.sh`

The build script will perform the following operations:
1. navigates to the Makefile directory 
    - `cd source/Makefile`
2. performs the `make` command to build the Makefile
3. runs the executable that is developed by the Makefile and runs the chatbot_driver Python script
    - `./kernel_module`
    - `python3 chatbot_driver.py`