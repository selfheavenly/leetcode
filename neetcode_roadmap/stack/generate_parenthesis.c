#include <stdlib.h>
#include <string.h>

void backtrack(char** result, int* returnSize, char* current, int pos, int open, int close, int max) {
    if (pos == max * 2) {
        current[pos] = '\0';
        result[*returnSize] = strdup(current);
        (*returnSize)++;
        return;
    }

    if (open < max) {
        current[pos] = '(';
        backtrack(result, returnSize, current, pos + 1, open + 1, close, max);
    }

    if (close < open) {
        current[pos] = ')';
        backtrack(result, returnSize, current, pos + 1, open, close + 1, max);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** generateParenthesis(int n, int* returnSize) {
    *returnSize = 0;
    int maxCombinations = 1 << (n * 2);
    char** result = (char**)malloc(maxCombinations * sizeof(char*));
    char* current = (char*)malloc((2 * n + 1) * sizeof(char));

    backtrack(result, returnSize, current, 0, 0, 0, n);
    
    free(current);
    return result;
}