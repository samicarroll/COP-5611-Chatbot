import os
import json

# Path to the character device file
DEVICE_FILE = "/dev/chatbot_device"

def send_input_to_kernel(input_text):
    with open(DEVICE_FILE, "w") as device:
        request = {"input": input_text}
        device.write(json.dumps(request))

def read_response_from_kernel():
    with open(DEVICE_FILE, "r") as device:
        response = device.read()
        return json.loads(response)

def main():
    print("Welcome to Chatbot!")
    print("Type your messages, or type 'quit' to exit.")
    while True:
        user_input = input("You: ")
        if user_input.lower() == "quit":
            print("Exiting Chatbot.")
            break
        send_input_to_kernel(user_input)
        response = read_response_from_kernel()
        print("Chatbot:", response["output"])

if __name__ == "__main__":
    main()