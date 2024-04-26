import openai

# Set your OpenAI API key
openai.api_key = ''

def send_input_to_openai(input_str):
    response = openai.Completion.create(
        engine="davinci",
        prompt=input_str,
        max_tokens=50
    )
    return response.choices[0].text.strip()

def main():
    print("Welcome to Chatbot!")
    print("Type your messages, or type 'quit' or 'q' to exit.")
    while True:
        user_input = input("You: ")
        if user_input.lower() in ["quit", "q"]:
            print("Exiting Chatbot.")
            break
        response = send_input_to_openai(user_input)
        print("Chatbot:", response)

if __name__ == "__main__":
    main()
