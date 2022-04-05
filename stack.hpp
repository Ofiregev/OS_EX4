#include <string>

#define INIT_SIZE 5

class Stack {
    std::string *stack = new std::string[INIT_SIZE]; 
    
    int size = INIT_SIZE;
    int pointer = 0;
    
    public:
        ~Stack();
        bool push(std::string text);
        std::string top();
        bool pop();

};