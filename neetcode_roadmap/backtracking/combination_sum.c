#include <stdio.h>
#include <stdlib.h>

void backtrack(int* candidates, int candidates_size, int target, int start, int* combination, int comb_size, int** result, int* return_size, int* return_column_sizes) {
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
        if (candidates[i] > target) continue;
        combination[comb_size] = candidates[i];
        backtrack(candidates, candidates_size, target - candidates[i], i, combination, comb_size + 1, result, return_size, return_column_sizes);
    }
}

int** combination_sum(int* candidates, int candidates_size, int target, int* return_size, int** return_column_sizes) {
    int max_combinations = 150;
    int** result = (int**)malloc(max_combinations * sizeof(int*));
    *return_column_sizes = (int*)malloc(max_combinations * sizeof(int));
    *return_size = 0;
    int* combination = (int*)malloc(target * sizeof(int));

    backtrack(candidates, candidates_size, target, 0, combination, 0, result, return_size, *return_column_sizes);

    free(combination);
    return result;
}
