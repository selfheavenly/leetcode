#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void backtrack(int* nums, int nums_size, int start, int* subset, int subset_size, int** result, int* return_size, int* return_column_sizes) {
    result[*return_size] = (int*)malloc(subset_size * sizeof(int));
    for (int i = 0; i < subset_size; i++) {
        result[*return_size][i] = subset[i];
    }
    return_column_sizes[*return_size] = subset_size;
    (*return_size)++;

    for (int i = start; i < nums_size; i++) {
        if (i > start && nums[i] == nums[i - 1]) continue;
        subset[subset_size] = nums[i];
        backtrack(nums, nums_size, i + 1, subset, subset_size + 1, result, return_size, return_column_sizes);
    }
}

int** subsets_with_dup(int* nums, int nums_size, int* return_size, int** return_column_sizes) {
    qsort(nums, nums_size, sizeof(int), compare);

    int max_subsets = 1 << nums_size;
    int** result = (int**)malloc(max_subsets * sizeof(int*));
    *return_column_sizes = (int*)malloc(max_subsets * sizeof(int));
    *return_size = 0;
    int* subset = (int*)malloc(nums_size * sizeof(int));

    backtrack(nums, nums_size, 0, subset, 0, result, return_size, *return_column_sizes);

    free(subset);
    return result;
}
