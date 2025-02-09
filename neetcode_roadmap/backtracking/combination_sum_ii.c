#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void backtrack(int* candidates, int candidates_size, int target, int start, int* combination, int comb_size, int** result, int* return_size, int* return_column_sizes, int* used) {
    if (target == 0) {
        result[*return_size] = (int*)malloc(comb_size * sizeof(int));
        for (int i = 0; i < comb_size; i++) {
            result[*return_size][i] = combination[i];
        }
        return_column_sizes[*return_size] = comb_size;
        (*return_size)++;
        return;
    }

    for (int i = start; i < candidates_size; i++) {
        if (i > start && candidates[i] == candidates[i - 1]) continue;
        if (candidates[i] > target) break;

        combination[comb_size] = candidates[i];
        backtrack(candidates, candidates_size, target - candidates[i], i + 1, combination, comb_size + 1, result, return_size, return_column_sizes, used);
    }
}

int** combination_sum2(int* candidates, int candidates_size, int target, int* return_size, int** return_column_sizes) {
    qsort(candidates, candidates_size, sizeof(int), compare);

    int max_combinations = 150;
    int** result = (int**)malloc(max_combinations * sizeof(int*));
    *return_column_sizes = (int*)malloc(max_combinations * sizeof(int));
    *return_size = 0;
    int* combination = (int*)malloc(candidates_size * sizeof(int));
    int* used = (int*)calloc(candidates_size, sizeof(int));

    backtrack(candidates, candidates_size, target, 0, combination, 0, result, return_size, *return_column_sizes, used);

    free(combination);
    free(used);
    return result;
}
