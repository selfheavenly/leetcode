#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct Stack {
    char* data;
    int top;
} Stack;

Stack* createStack(int size) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (char*)malloc(size * sizeof(char));
    stack->top = -1;
    return stack;
}

void push(Stack* stack, char ch) {
    stack->data[++(stack->top)] = ch;
}

char pop(Stack* stack) {
    return stack->data[(stack->top)--];
}

char peek(Stack* stack) {
    return stack->data[stack->top];
}

bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

void freeStack(Stack* stack) {
    free(stack->data);
    free(stack);
}

bool isValid(char* s) {
    Stack* stack = createStack(strlen(s));
    for (int i = 0; s[i] != '\0'; i++) {
        char ch = s[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            push(stack, ch);
        } else {
            if (isEmpty(stack)) {
                freeStack(stack);
                return false;
            }
            char top = peek(stack);
            if ((ch == ')' && top == '(') || 
                (ch == '}' && top == '{') || 
                (ch == ']' && top == '[')) {
                pop(stack);
            } else {
                freeStack(stack);
                return false;
            }
        }
    }
    bool result = isEmpty(stack);
    freeStack(stack);
    return result;
}