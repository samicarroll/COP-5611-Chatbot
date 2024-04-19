import os
import fcntl
import requests

# URL and API key for accessing the chatGPT API
CHATGPT_API_URL = "https://api.openai.com/v1/chat/completions"

# TODO: ADD OPENAI API KEY BEFORE RUNNING build.sh!
OPENAI_API_KEY = 

# define the IOCTL commands
IOCTL_CHATGPT_QUERY = 0x1000

# function to interact with the ChatGPT API
def chat_with_gpt(prompt):
    # construct HTTP headers for the API request
    headers = {
        "Authorization": f"Bearer {OPENAI_API_KEY}",
        "Content-Type": "application/json"
    }
    # data to send in the API request
    data = {
        "model": "text-davinci-002",  # Specify the GPT model to use
        "messages": [{"role": "user", "content": prompt}]  # Prompt for GPT
    }
    # send POST request to chatGPT API
    response = requests.post(CHATGPT_API_URL, json=data, headers=headers)
    # extract and return the generated text from API response
    return response.json()["choices"][0]["text"]

# define the character device class
class ChatbotDriver:
    def __init__(self):
        # initialize buffer for storing chatGPT response
        self.buffer = ""

    # IOCTL handler
    def ioctl(self, cmd, arg):
        if cmd == IOCTL_CHATGPT_QUERY:
            # call function to interact with chatGPT API using provided prompt
            self.buffer = chat_with_gpt(arg.decode())
            # return length of generated response
            return len(self.buffer)
        else:
            # return error for unknown IOCTL command
            return -1

def main():
    chatbot = ChatbotDriver()
    # open device file corresponding to the chatbot driver
    chatbot_device = os.open("/dev/chatbot", os.O_RDWR)

    while True:
        # get user input query
        query = input("You: ")
        # exit loop if user input is "exit"
        if query.lower() == "exit":
            break

        # write user input to the device file
        os.write(chatbot_device, query.encode())
        # call IOCTL to interact with chatGPT API and get response length
        response = fcntl.ioctl(chatbot_device, IOCTL_CHATGPT_QUERY, b"")
        # read the generated response from the device file
        result = os.read(chatbot_device, response).decode()
        # print the response from chatGPT
        print("ChatGPT:", result)

    # close the device file
    os.close(chatbot_device)

if __name__ == "__main__":
    main()