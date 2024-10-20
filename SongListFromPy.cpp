#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <unistd.h> /*PROGRAM RUNS ON LINUX AND MACOS ENVIRONMENT NOT WINDOWS*/
#include <string>
#include <fstream>
#include <sstream>

std::string InputString;
/*Use above as space for actual input from program in form "Question? Answer, Question? Answer, ...." extracted from user answers*/
std::string OutputString;
bool pythonFileReturned = false;

void readFileIntoString() {
    std::ifstream file("quiz-results.txt");

    if (!file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        exit(0);
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    InputString = buffer.str();

    file.close();
}

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
    readFileIntoString();
    callPythonFile();

    if (pythonFileReturned == true) {
        OutputString = readOutputString();
    }
    else {
        std::cout << "PythonFileReturn Failed" << std::endl;
        exit(0);
    }
    /*std::cout << OutputString << std::endl; For debugging purposes*/

    std::ofstream outFile("output.txt");
    outFile << OutputString;
    outFile.close();

    return 0;
}