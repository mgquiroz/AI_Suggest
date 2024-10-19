import os
import google.generativeai as genai

model = genai.GenerativeModel("gemini-1.5-flash")
KEY = "AIzaSyDNsKtVWAcW-QlMq23ON1mSF3GKcU6Vovs"
#AIzaSyDNsKtVWAcW-QlMq23ON1mSF3GKcU6Vovs
genai.configure(api_key=KEY)

def main():
    prompt = input("Enter your prompt: ")
    prompt = "Please provide a list of five songs along with their author in the following format (Song_Name by Author); ensuring the format of a comma separated list, such that the songs are most likely to be enjoyed by the person described by the following questions and answers. DO NOT INCLUDE ANY ADDITIONAL TEXT, SPACES, OR ANY OTHER OUTPUT BESIDES THE LIST: " + prompt
    response = model.generate_content(prompt)
    print(response.text)

if __name__ == "__main__":
    main()