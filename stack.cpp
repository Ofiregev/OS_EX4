// global variable:
// vector of strings, each string is 1024 bytes
// 

// PUSH
// push pushs a new value into the stack


// POP
// pop returns and deletes the top value in the stack

// TOP
// top returns the top value in the stack


#include <string>
#include <iostream>
#include <cstdlib>
int main () {
    bool running = true;
    while (running) {
        std::string command; 
        std::cin >> command;
        if (command == "PUSH") {
            std::string line;
            std::getline(std::cin, line);
            std::cout << line;
        } else if (command == "POP") {

        } else if (command == "TOP") {

        } else if (command == "EXIT") {
            running = false;
        }
        

    }

    return 1;

}