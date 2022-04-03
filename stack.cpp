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
#define INIT_SIZE 5
using namespace std;

class stack {
    string stack[INIT_SIZE]; 
    int size = 5;
    int pointer = 0;

    public:
    // stack() {

    // }
    bool push(string text) {
        if (pointer==size-1) {
            return false; 
            // RESIZE THE STACK
        }
        stack[pointer++] = text;
        return true;
    }

    string top() {
        if (pointer == 0) {
            return "STACK EMPTY!";
        }
        return stack[pointer-1];
    }

    bool pop() {
        if (pointer == 0) {
            return false; 
        }
        pointer--;
        return true;
    }
};




int main () {
    bool running = true;
    stack stack;
    while (running) {
        string command; 
        cin >> command;
        if (command == "PUSH") {
            string line;
            getline(cin, line);
            if (!stack.push(line)) {
                cout << "PUSH failed\n";
            };
        } else if (command == "POP") {
            if (!stack.pop()) {
                cout << "POP failed\n";
            } else {
                cout << "POPPED\n";
            }
        } else if (command == "TOP") {
            cout << "OUTPUT: " << stack.top() << endl;
        } else if (command == "EXIT") {
            running = false;
        }
        

    }

    return 1;

}