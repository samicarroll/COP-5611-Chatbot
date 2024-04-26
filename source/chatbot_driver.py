def send_input_to_kernel(input_str):
    with open("/dev/chatbot", "w") as device:
        device.write(input_str)

def read_response_from_kernel():
    with open("/dev/chatbot", "r") as device:
        response = device.read()
        return response

def main():
    print("Welcome to Chatbot!")
    print("Type your messages, or type 'quit' or 'q' to exit.")
    while True:
        user_input = input("You: ")
        if user_input.lower() in ["quit", "q"]:
            print("Exiting Chatbot.")
            break
        send_input_to_kernel(user_input)
        response = read_response_from_kernel()
        print("Chatbot:", response)

if __name__ == "__main__":
    main()
