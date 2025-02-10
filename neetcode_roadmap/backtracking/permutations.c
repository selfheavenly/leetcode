#include <stdio.h>
#include <stdlib.h>

void backtrack(int* nums, int nums_size, int* used, int* permutation, int perm_size, int** result, int* return_size, int* return_column_sizes) {
    if (perm_size == nums_size) {
        result[*return_size] = (int*)malloc(nums_size * sizeof(int));
        for (int i = 0; i < nums_size; i++) {
            result[*return_size][i] = permutation[i];
        }
        return_column_sizes[*return_size] = nums_size;
        (*return_size)++;
        return;
    }

    for (int i = 0; i < nums_size; i++) {
        if (used[i]) continue;
        used[i] = 1;
        permutation[perm_size] = nums[i];
        backtrack(nums, nums_size, used, permutation, perm_size + 1, result, return_size, return_column_sizes);
        used[i] = 0;
    }
}

int** permute(int* nums, int nums_size, int* return_size, int** return_column_sizes) {
    int max_permutations = 1;
    for (int i = 2; i <= nums_size; i++) max_permutations *= i;

    int** result = (int**)malloc(max_permutations * sizeof(int*));
    *return_column_sizes = (int*)malloc(max_permutations * sizeof(int));
    *return_size = 0;
    int* permutation = (int*)malloc(nums_size * sizeof(int));
    int* used = (int*)calloc(nums_size, sizeof(int));

    backtrack(nums, nums_size, used, permutation, 0, result, return_size, *return_column_sizes);

    free(permutation);
    free(used);
    return result;
}
