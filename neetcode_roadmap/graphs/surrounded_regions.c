#include <stdio.h>

void dfs(char** board, int rows, int cols, int r, int c) {
    if (r < 0 || c < 0 || r >= rows || c >= cols || board[r][c] != 'O') 
        return;

    board[r][c] = 'T'; 

    dfs(board, rows, cols, r - 1, c);
    dfs(board, rows, cols, r + 1, c);
    dfs(board, rows, cols, r, c - 1);
    dfs(board, rows, cols, r, c + 1);
}

void solve(char** board, int board_size, int* board_col_size) {
    int rows = board_size, cols = *board_col_size;

    for (int i = 0; i < rows; i++) {
        dfs(board, rows, cols, i, 0);
        dfs(board, rows, cols, i, cols - 1);
    }
    for (int j = 0; j < cols; j++) {
        dfs(board, rows, cols, 0, j);
        dfs(board, rows, cols, rows - 1, j);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == 'O') {
                board[i][j] = 'X';
            } else if (board[i][j] == 'T') {
                board[i][j] = 'O';
            }
        }
    }
}
