import os
import openai

# Set your OpenAI API key here
openai.api_key = ''

DEVICE_FILE = "/dev/chatbot"

def read_response():
    with open(DEVICE_FILE, "r") as device:
        response = device.read()
        return response

def write_input(input_str):
    with open(DEVICE_FILE, "w") as device:
        device.write(input_str)

def main():
    print("Chatbot Helper: Running")
    while True:
        user_input = input("User input: ")
        if user_input.lower() in ["quit", "q"]:
            break
        write_input(user_input)
        # Simulate processing delay or other tasks
        response = read_response()
        print("Chatbot response:", response)

if __name__ == "__main__":
    main()
