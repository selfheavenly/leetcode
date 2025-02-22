#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row, col;
} QueueNode;

int oranges_rotting(int** grid, int grid_size, int* grid_col_size) {
    int rows = grid_size, cols = *grid_col_size;
    int fresh_oranges = 0, minutes = 0;
    
    int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    QueueNode queue[rows * cols];
    int front = 0, rear = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 2) {
                queue[rear++] = (QueueNode){r, c};
            } else if (grid[r][c] == 1) {
                fresh_oranges++;
            }
        }
    }

    if (fresh_oranges == 0) return 0;

    while (front < rear) {
        int level_size = rear - front;
        int rotted = 0;

        for (int i = 0; i < level_size; i++) {
            QueueNode node = queue[front++];
            for (int d = 0; d < 4; d++) {
                int new_r = node.row + directions[d][0];
                int new_c = node.col + directions[d][1];

                if (new_r >= 0 && new_r < rows && new_c >= 0 && new_c < cols && grid[new_r][new_c] == 1) {
                    grid[new_r][new_c] = 2;
                    queue[rear++] = (QueueNode){new_r, new_c};
                    fresh_oranges--;
                    rotted = 1;
                }
            }
        }
        
        if (rotted) minutes++;
    }

    return (fresh_oranges == 0) ? minutes : -1;
}
