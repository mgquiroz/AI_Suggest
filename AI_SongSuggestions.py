import os
import google.generativeai as genai

model = genai.GenerativeModel("gemini-1.5-flash")
KEY = "AIzaSyDNsKtVWAcW-QlMq23ON1mSF3GKcU6Vovs"
#AIzaSyDNsKtVWAcW-QlMq23ON1mSF3GKcU6Vovs
genai.configure(api_key=KEY)

def main():
    #Expected input format
    # Question? Answer, Question? Answer, Question? Answer, ....
    prompt = "Please provide a list of five songs along with their author in the following format (Song_Name by Author); ensuring the format of a comma separated list, such that the songs are most likely to be enjoyed by the person described by the following questions and answers. DO NOT INCLUDE ANY ADDITIONAL TEXT, SPACES, OR ANY OTHER OUTPUT BESIDES THE LIST: " + os.environ.get('InputString')
    Song_Suggestions = model.generate_content(prompt)
    with open("OutputString.txt", "w") as OutputString:
        OutputString.write(Song_Suggestions.text)

if __name__ == "__main__":
    main()