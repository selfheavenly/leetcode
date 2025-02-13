#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALLOC_SIZE  (2)
#define CPY_BUF_SIZE  (1<<20)
#define PTR_BUF_SIZE  (1<<10)

void preprocess_palindrome_dp(char* s, int str_len, bool** dp) {
    for (int i = 0; i < str_len; i++) {
        dp[i][i] = true;
    }
    for (int length = 2; length <= str_len; length++) {
        for (int start = 0; start <= str_len - length; start++) {
            int end = start + length - 1;
            if (s[start] == s[end]) {
                dp[start][end] = (length == 2) || dp[start + 1][end - 1];
            }
        }
    }
}

void backtrack(char* s, int* return_size, int** return_column_sizes, char**** result, int* alloc_result, char* string_temp, int temp_index, int* string_ptr, int ptr_len, char** cpy_buffer, int* cpy_buffer_index, char*** ptr_buffer, int* ptr_buffer_index, int start, int str_len, bool** dp) {
    int index;
    int string_pos;
    char** cpy_ptr;
    char* cpy_string;

    if (start >= str_len) {
        if (*return_size >= *alloc_result) {
            (*alloc_result) *= 2;
            (*result) = (char***) realloc(*result, *alloc_result * sizeof(char**));
            *return_column_sizes = (int*) realloc(*return_column_sizes, *alloc_result * sizeof(int));
        }

        if ((*cpy_buffer_index + temp_index) < CPY_BUF_SIZE) {
            cpy_string = &(*cpy_buffer)[*cpy_buffer_index];
            (*cpy_buffer_index) += temp_index;
        } else {
            *cpy_buffer = (char*) malloc(sizeof(char) * CPY_BUF_SIZE);
            *cpy_buffer_index = 0;
            cpy_string = &(*cpy_buffer)[*cpy_buffer_index];
            (*cpy_buffer_index) += temp_index;
        }

        if ((*ptr_buffer_index + ptr_len) < PTR_BUF_SIZE) {
            cpy_ptr = &(*ptr_buffer)[*ptr_buffer_index];
            (*ptr_buffer_index) += ptr_len;
        } else {
            *ptr_buffer = (char**) malloc(sizeof(char*) * PTR_BUF_SIZE);
            *ptr_buffer_index = 0;
            cpy_ptr = &(*ptr_buffer)[*ptr_buffer_index];
            (*ptr_buffer_index) += ptr_len;
        }

        memcpy(cpy_string, string_temp, sizeof(char) * temp_index);
        for (index = 0; index < ptr_len; index++) {
            cpy_ptr[index] = &cpy_string[string_ptr[index]];
        }

        (*return_column_sizes)[*return_size] = ptr_len;
        (*result)[*return_size] = cpy_ptr;
        (*return_size)++;
        return;
    }

    for (index = start; index < str_len; index++) {
        if (dp[start][index]) { 
            string_pos = temp_index + (index - start);
            memcpy(string_temp + temp_index, s + start, index - start + 1);
            string_temp[string_pos + 1] = '\0';

            string_ptr[ptr_len] = temp_index;
            backtrack(s, return_size, return_column_sizes, result, alloc_result, string_temp, string_pos + 2, string_ptr, ptr_len + 1, cpy_buffer, cpy_buffer_index, ptr_buffer, ptr_buffer_index, index + 1, str_len, dp);
        }
    }
}

char*** partition(char* s, int* return_size, int** return_column_sizes) {
    char*** result;
    char* string_temp;
    int* string_ptr;
    int str_len;
    int alloc_result;
    char* cpy_buffer;
    int cpy_buffer_index;
    char** ptr_buffer;
    int ptr_buffer_index;

    str_len = strlen(s);
    alloc_result = ALLOC_SIZE;
    result = (char***) malloc(sizeof(char**) * alloc_result);
    *return_column_sizes = (int*) malloc(alloc_result * sizeof(int));
    string_temp = (char*) malloc(sizeof(char) * str_len * 2);
    string_ptr = (int*) malloc(sizeof(int) * str_len);
    cpy_buffer = (char*) malloc(sizeof(char) * CPY_BUF_SIZE);
    cpy_buffer_index = 0;
    ptr_buffer = (char**) malloc(sizeof(char*) * PTR_BUF_SIZE);
    ptr_buffer_index = 0;
    *return_size = 0;

    bool** dp = (bool**) malloc(sizeof(bool*) * str_len);
    for (int i = 0; i < str_len; i++) {
        dp[i] = (bool*) calloc(str_len, sizeof(bool));
    }
    preprocess_palindrome_dp(s, str_len, dp);

    backtrack(s, return_size, return_column_sizes, &result, &alloc_result, string_temp, 0, string_ptr, 0, &cpy_buffer, &cpy_buffer_index, &ptr_buffer, &ptr_buffer_index, 0, str_len, dp);

    for (int i = 0; i < str_len; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}
