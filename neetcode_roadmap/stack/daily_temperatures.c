#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    *returnSize = temperaturesSize;
    int* answer = (int*)calloc(temperaturesSize, sizeof(int));

    int stack[temperaturesSize];
    int top = -1;

    for (int i = 0; i < temperaturesSize; i++) {
        // Check if stack isnt empty (>= 0) and then compare current idx to stack val
        while (top >= 0 && temperatures[i] > temperatures[stack[top]]) {
            int index = stack[top--];
            answer[index] = i - index;
        }
        stack[++top] = i;
    }
    
    return answer;
}