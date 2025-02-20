#include <stdio.h>

int dfs(int** grid, int m, int n, int row, int col) {
    if (row < 0 || col < 0 || row >= m || col >= n || grid[row][col] == 0) 
        return 0;

    grid[row][col] = 0;  // Mark cell as visited

    return 1 + 
        dfs(grid, m, n, row + 1, col) + // Down
        dfs(grid, m, n, row - 1, col) + // Up
        dfs(grid, m, n, row, col + 1) + // Right
        dfs(grid, m, n, row, col - 1);  // Left
}

int max_area_of_island(int** grid, int grid_size, int* grid_col_size) {
    if (!grid || grid_size == 0) return 0;

    int max_area = 0;
    
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_col_size[i]; j++) {  
            if (grid[i][j] == 1) {  // Found new island
                int area = dfs(grid, grid_size, grid_col_size[i], i, j);
                if (area > max_area) {
                    max_area = area;
                }
            }
        }
    }

    return max_area;
}
