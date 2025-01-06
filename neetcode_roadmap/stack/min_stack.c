#include <stdlib.h>
#include <limits.h>

typedef struct {
    int* stack;
    int top;
    int* minStack;
    int minTop;
    int capacity;
} MinStack;

MinStack* minStackCreate() {
    MinStack* obj = (MinStack*)malloc(sizeof(MinStack));
    // Set initial capacity
    obj->capacity = 128;
    obj->stack = (int*)malloc(obj->capacity * sizeof(int));
    obj->minStack = (int*)malloc(obj->capacity * sizeof(int));
    obj->top = -1;
    obj->minTop = -1;
    return obj;
}

void minStackPush(MinStack* obj, int val) {
    if (obj->top + 1 == obj->capacity) {
        // Double the capacity if full
        obj->capacity *= 2;
        obj->stack = (int*)realloc(obj->stack, obj->capacity * sizeof(int));
        obj->minStack = (int*)realloc(obj->minStack, obj->capacity * sizeof(int));
    }
    obj->stack[++(obj->top)] = val;

    // Update the min stack
    if (obj->minTop == -1 || val <= obj->minStack[obj->minTop]) {
        obj->minStack[++(obj->minTop)] = val;
    }
}

void minStackPop(MinStack* obj) {
    if (obj->top == -1) return;

    // Pop the main stack
    int poppedValue = obj->stack[obj->top--];

    // Pop the min stack if the popped value matches the top of the min stack
    if (poppedValue == obj->minStack[obj->minTop]) {
        obj->minTop--;
    }
}

int minStackTop(MinStack* obj) {
    // Handle empty stack case
    if (obj->top == -1) return INT_MIN;
    return obj->stack[obj->top];
}

int minStackGetMin(MinStack* obj) {
    // Handle empty stack case
    if (obj->minTop == -1) return INT_MIN;
    return obj->minStack[obj->minTop];
}

void minStackFree(MinStack* obj) {
    free(obj->stack);
    free(obj->minStack);
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/