#include <stdlib.h>

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {

    // Value Recycling
    int *left = &numbers[0]; 
    int *right = &numbers[numbersSize - 1]; 

    *returnSize = 2;
    int *solution = malloc(sizeof(int)*2); 

    while (left < right) {
        int sum = *left + *right;
        if (sum == target) {
            solution[0] = left - numbers + 1;
            solution[1] = right - numbers + 1;
            break;
        }
        if (sum < target) left++;
        else right--;
    }

    return solution;
}