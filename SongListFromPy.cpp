#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <string>
#include <fstream>

std::string InputString = "Gender? Male, Age? 21, Personality? Extroverted, Cats or Dogs? Cats";
/*Use above as space for actual input from program in form "Question? Answer, Question? Answer, ...." extracted from user answers*/
std::string OutputString;
bool pythonFileReturned = false;

void callPythonFile(){
    setenv("InputString", InputString.c_str(), 1);
    int callStatus = system("python AI_SongSuggestions.py");
    if (callStatus == 0) {
    pythonFileReturned = true;
    } 
    else {
    std::cout << "Program failed to run Python file." << std::endl;
    exit(0);
    }
}
std::string readOutputString(){
    std::ifstream infile("OutputString.txt");
    std::string OutputString;
    if (infile.is_open()){
        std::getline(infile, OutputString);
        infile.close();
    }
    else{
        std::cout << "Program failed to read text file." << std::endl;
        exit(0);
    }
    return OutputString;
}

int main(){

    callPythonFile();
    if (pythonFileReturned == true) {
        OutputString = readOutputString();
    }
    else {
        std::cout << "PythonFileReturn Failed" << std::endl;
        exit(0);
    }
    std::cout << OutputString << std::endl;

    return 0;
}