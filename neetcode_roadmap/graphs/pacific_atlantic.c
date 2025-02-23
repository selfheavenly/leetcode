#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row, col;
} Pair;

void dfs(int** heights, int rows, int cols, int r, int c, int** ocean) {
    static int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    ocean[r][c] = 1; 

    for (int d = 0; d < 4; d++) {
        int new_r = r + directions[d][0];
        int new_c = c + directions[d][1];

        if (new_r >= 0 && new_r < rows && new_c >= 0 && new_c < cols &&
            !ocean[new_r][new_c] && heights[new_r][new_c] >= heights[r][c]) {
            dfs(heights, rows, cols, new_r, new_c, ocean);
        }
    }
}

int** pacific_atlantic(int** heights, int heights_size, int* heights_col_size, int* return_size, int** return_column_sizes) {
    int rows = heights_size, cols = *heights_col_size;
    *return_size = 0;

    int** pacific = (int**)malloc(rows * sizeof(int*));
    int** atlantic = (int**)malloc(rows * sizeof(int*));
    int** result = (int**)malloc(rows * cols * sizeof(int*));
    *return_column_sizes = (int*)malloc(rows * cols * sizeof(int));

    for (int i = 0; i < rows; i++) {
        pacific[i] = (int*)calloc(cols, sizeof(int));
        atlantic[i] = (int*)calloc(cols, sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        dfs(heights, rows, cols, i, 0, pacific);      // Pacific Left Border
        dfs(heights, rows, cols, i, cols - 1, atlantic); // Atlantic Right Border
    }
    for (int j = 0; j < cols; j++) {
        dfs(heights, rows, cols, 0, j, pacific);      // Pacific Top Border
        dfs(heights, rows, cols, rows - 1, j, atlantic); // Atlantic Bottom Border
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (pacific[i][j] && atlantic[i][j]) {
                result[*return_size] = (int*)malloc(2 * sizeof(int));
                result[*return_size][0] = i;
                result[*return_size][1] = j;
                (*return_column_sizes)[*return_size] = 2;
                (*return_size)++;
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        free(pacific[i]);
        free(atlantic[i]);
    }
    free(pacific);
    free(atlantic);

    return result;
}
