#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int evalRPN(char** tokens, int tokensSize) {
    int* stack = (int*)malloc(tokensSize * sizeof(int));
    int top = -1;

    for (int i = 0; i < tokensSize; i++) {
        char* token = tokens[i];

        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || 
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
            
            int b = stack[top--];
            int a = stack[top--];
            int result = 0;

            if (strcmp(token, "+") == 0) result = a + b;
            else if (strcmp(token, "-") == 0) result = a - b;
            else if (strcmp(token, "*") == 0) result = a * b;
            else if (strcmp(token, "/") == 0) result = a / b;

            stack[++top] = result;

        } else {
            stack[++top] = atoi(token);
        }
    }

    int result = stack[top];
    free(stack);
    return result;
}