#include <stdlib.h>

int** insert(int** intervals, int intervals_size, int* intervals_col_size, int* new_interval, int new_interval_size, int* return_size, int** return_column_sizes) {
    int** result = (int**)malloc((intervals_size + 1) * sizeof(int*));
    *return_column_sizes = (int*)malloc((intervals_size + 1) * sizeof(int));
    
    int i = 0, count = 0;
    
    while (i < intervals_size && intervals[i][1] < new_interval[0]) {
        result[count] = intervals[i];
        (*return_column_sizes)[count++] = 2;
        i++;
    }

    while (i < intervals_size && intervals[i][0] <= new_interval[1]) {
        new_interval[0] = (new_interval[0] < intervals[i][0]) ? new_interval[0] : intervals[i][0];
        new_interval[1] = (new_interval[1] > intervals[i][1]) ? new_interval[1] : intervals[i][1];
        i++;
    }
    
    result[count] = (int*)malloc(2 * sizeof(int));
    result[count][0] = new_interval[0];
    result[count][1] = new_interval[1];
    (*return_column_sizes)[count++] = 2;

    while (i < intervals_size) {
        result[count] = intervals[i];
        (*return_column_sizes)[count++] = 2;
        i++;
    }

    *return_size = count;
    return result;
}
