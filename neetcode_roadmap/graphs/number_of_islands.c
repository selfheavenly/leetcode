#include <stdio.h>

void dfs(char** grid, int m, int n, int row, int col) {
    if (row < 0 || col < 0 || row >= m || col >= n || grid[row][col] == '0') 
        return;
    
    grid[row][col] = '0'; // Mark as visited
    
    dfs(grid, m, n, row + 1, col); // Down
    dfs(grid, m, n, row - 1, col); // Up
    dfs(grid, m, n, row, col + 1); // Right
    dfs(grid, m, n, row, col - 1); // Left
}

int num_islands(char** grid, int grid_size, int* grid_col_size) {
    if (!grid || grid_size == 0) return 0;
    
    int islands = 0;
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_col_size[i]; j++) {
            if (grid[i][j] == '1') {
                islands++;
                dfs(grid, grid_size, grid_col_size[i], i, j);
            }
        }
    }
    return islands;
}
