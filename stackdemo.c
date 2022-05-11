#include "stack.h"
#include <stdbool.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

int pos = sizeof(struct node); // initial position for the most bottom value in the stack

char* CURR_ADDRESS;
int MEMORY_INITIALIZED = 0;

void setpos(struct node* position) {
    CURR_ADDRESS = (char*)position;    
}

void* Mem_Init(int sizeOfRegion){
   
    CURR_ADDRESS = (char*)mmap(NULL, sizeOfRegion, PROT_READ | PROT_WRITE, MAP_ANON|MAP_SHARED, -1,0);

    if ((void *) -1 == CURR_ADDRESS) {
        printf("Could not map memory: %s\n", strerror(errno));
    }

    printf("curr before all: %p\n\n", CURR_ADDRESS);

    void* startingHeader = CURR_ADDRESS;

    //rest of the fontion
    return startingHeader;
}

void* _malloc (size_t size) {
    CURR_ADDRESS = CURR_ADDRESS+sizeof(struct node);
    brk(CURR_ADDRESS);
    // pos += sizeof(struct node);
    return CURR_ADDRESS;
}

void _free (void* ptr) {
    // printf(" cur before free in freefunc free %p\n", CURR_ADDRESS);
   CURR_ADDRESS = CURR_ADDRESS-sizeof(struct node);
   brk(CURR_ADDRESS);
   ptr = CURR_ADDRESS;
//    printf(" after free: %p\n", ptr);
    
}



bool push(struct stack *stack, char* text) {
    
    struct node *newNode = (struct node*)_malloc(sizeof(struct node));
    strcpy(newNode->text, text);
    if (stack->isEmpty) {
        stack->ptr = newNode;
        stack->isEmpty = false;
    } else {
        newNode->prev = stack->ptr;
        stack->ptr = newNode;
    }
    setpos(&(stack->ptr));
    return true;
}

bool pop(struct stack *stack) {

    if (stack->isEmpty) {
        return false;
    }
    struct node *tempNode = stack->ptr;
    _free(stack->ptr);
    if (tempNode->prev == NULL) {
        stack->isEmpty = true;
        stack->ptr = NULL;
        return true;
    }
    tempNode->prev->next = NULL;
    stack->ptr = stack->ptr->prev;
    

    return true;
}
char* top(struct stack stack) {
    setpos(&(stack.ptr));
    if (!stack.ptr) {
        char* emptyStack = "stack is empty!";
        return emptyStack;
    }
    return stack.ptr->text;
}

// int main() {
//      struct stack stack;
//     Mem_Init(102400);
//     // void *addr = _malloc(10);
//     // printf(" curr in main :%p \n",CURR_ADDRESS);

//     // _free(addr);
//     // printf("%p\n",addr);
//     push(&stack, "1");
//     printf(" curr after push 1 :%p \n",CURR_ADDRESS);

//     printf("%s\n", top(stack));
//     push(&stack, "2");
//     printf(" curr after push 2:%p \n",CURR_ADDRESS);

//     printf("%s\n", top(stack));
//     push(&stack, "3");
//     printf(" curr after push 3 :%p \n",CURR_ADDRESS);
//     printf("%s\n", top(stack));
//     pop(&stack);
//     printf(" curr after pop :%p \n",CURR_ADDRESS);
//     printf("%s\n", top(stack));
//     // wipe(stack);
// }