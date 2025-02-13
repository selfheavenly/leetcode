#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_palindrome(char* s, int start, int end) {
    while (start < end) {
        if (s[start++] != s[end--]) {
            return false;
        }
    }
    return true;
}

void backtrack(char* s, int start, char**** result, int* return_size, int** return_column_sizes, char** current_partition, int part_size) {
    if (s[start] == '\0') {
        (*result)[*return_size] = (char**)malloc(part_size * sizeof(char*));
        for (int i = 0; i < part_size; i++) {
            (*result)[*return_size][i] = strdup(current_partition[i]);
        }
        (*return_column_sizes)[*return_size] = part_size;
        (*return_size)++;
        return;
    }

    for (int end = start; s[end] != '\0'; end++) {
        if (is_palindrome(s, start, end)) {
            current_partition[part_size] = (char*)malloc((end - start + 2) * sizeof(char));
            strncpy(current_partition[part_size], &s[start], end - start + 1);
            current_partition[part_size][end - start + 1] = '\0';

            backtrack(s, end + 1, result, return_size, return_column_sizes, current_partition, part_size + 1);

            free(current_partition[part_size]); 
        }
    }
}

char*** partition(char* s, int* return_size, int** return_column_sizes) {
    int max_partitions = 1 << (strlen(s) - 1); 
    char*** result = (char***)malloc(max_partitions * sizeof(char**));
    *return_column_sizes = (int*)malloc(max_partitions * sizeof(int));
    *return_size = 0;
    char** current_partition = (char**)malloc(strlen(s) * sizeof(char*));

    backtrack(s, 0, &result, return_size, return_column_sizes, current_partition, 0);

    free(current_partition);
    return result;
}
