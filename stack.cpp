// global variable:
// vector of strings, each string is 1024 bytes
// 

// PUSH
// push pushs a new value into the stack


// POP
// pop returns and deletes the top value in the stack

// TOP
// top returns the top value in the stack


#include "stack.hpp"
#include <iostream>
#include <cstdlib>
#define INIT_SIZE 5
using namespace std;


  
    // Stack::stack() {

    // }

    Stack::~Stack() {
        delete[] stack;
    }
    bool Stack::push(string text) {
        if (pointer==size-1) {
            string *temp = new string[size];
            for (size_t i = 0; i < pointer; i++)
            {
                temp[i] = stack[i];
            }  
            delete[] stack;     
            stack = new string[size*2];
            size = size*2;
            for (size_t i = 0; i < pointer; i++)
            {
                stack[i] = temp[i];
            }
            delete[] temp;
        }
        stack[pointer++] = text;
        
        return true;
    }

    string Stack::top() {
        if (pointer == 0) {
            return "STACK EMPTY!";
        }
        return stack[pointer-1];
    }

    bool Stack::pop() {
        if (pointer == 0) {
            return false; 
        }
        pointer--;
        return true;
    }


// int main () {
//     bool running = true;
//     Stack stack;
//     while (running) {
//         string command; 
//         cin >> command;
//         if (command == "PUSH") {
//             string line;
//             getline(cin, line);
//             if (!stack.push(line)) {
//                 cout << "PUSH failed\n";
//             };
//         } else if (command == "POP") {
//             if (!stack.pop()) {
//                 cout << "POP failed\n";
//             } else {
//                 cout << "POPPED\n";
//             }
//         } else if (command == "TOP") {
//             cout << "OUTPUT: " << stack.top() << endl;
//         } else if (command == "EXIT") {
//             running = false;
//         }
        
//     }

//     return 1;

// }