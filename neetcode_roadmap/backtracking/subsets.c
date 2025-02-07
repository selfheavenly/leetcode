#include <stdio.h>
#include <stdlib.h>

void backtrack(int* nums, int nums_size, int** result, int* return_size, int* subset, int subset_size, int start, int* return_column_sizes) {
    result[*return_size] = (int*)malloc(subset_size * sizeof(int));
    for (int i = 0; i < subset_size; i++) {
        result[*return_size][i] = subset[i];
    }
    return_column_sizes[*return_size] = subset_size;
    (*return_size)++;

    for (int i = start; i < nums_size; i++) {
        subset[subset_size] = nums[i];
        backtrack(nums, nums_size, result, return_size, subset, subset_size + 1, i + 1, return_column_sizes);
    }
}

int** subsets(int* nums, int nums_size, int* return_size, int** return_column_sizes) {
    int max_subsets = 1 << nums_size;
    int** result = (int**)malloc(max_subsets * sizeof(int*));
    *return_column_sizes = (int*)malloc(max_subsets * sizeof(int));
    *return_size = 0;
    int* subset = (int*)malloc(nums_size * sizeof(int));

    backtrack(nums, nums_size, result, return_size, subset, 0, 0, *return_column_sizes);

    free(subset);
    return result;
}
