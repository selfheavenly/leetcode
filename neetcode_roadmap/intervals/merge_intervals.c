#include <stdlib.h>

int compare_intervals(const void* a, const void* b) {
    return ((int*)a)[0] - ((int*)b)[0];
}

int** merge(int** intervals, int intervals_size, int* intervals_col_size, int* return_size, int** return_column_sizes) {
    if (intervals_size == 0) {
        *return_size = 0;
        *return_column_sizes = NULL;
        return NULL;
    }

    qsort(intervals, intervals_size, sizeof(int*), compare_intervals);

    int** result = (int**)malloc(intervals_size * sizeof(int*));
    *return_column_sizes = (int*)malloc(intervals_size * sizeof(int));
    
    int count = 0;
    result[count] = (int*)malloc(2 * sizeof(int));
    result[count][0] = intervals[0][0];
    result[count][1] = intervals[0][1];

    for (int i = 1; i < intervals_size; i++) {
        if (intervals[i][0] <= result[count][1]) {
            result[count][1] = (intervals[i][1] > result[count][1]) ? intervals[i][1] : result[count][1];
        } else {
            count++;
            result[count] = (int*)malloc(2 * sizeof(int));
            result[count][0] = intervals[i][0];
            result[count][1] = intervals[i][1];
        }
    }

    *return_size = count + 1;
    for (int i = 0; i < *return_size; i++) {
        (*return_column_sizes)[i] = 2;
    }

    return result;
}
