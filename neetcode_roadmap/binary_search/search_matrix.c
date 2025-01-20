#include <stdbool.h>
#include <stdlib.h>

bool search_matrix(int** matrix, int matrix_size, int* matrix_col_size, int target) {
    int m = matrix_size;
    int n = matrix_col_size[0];
    int left = 0, right = m * n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int row = mid / n;
        int col = mid % n;
        int mid_value = matrix[row][col];

        if (mid_value == target) {
            return true;
        } else if (mid_value < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return false;
}