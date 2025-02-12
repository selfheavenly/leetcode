#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool backtrack(char **board, int board_size, int board_col_size, char *word, int index, int row, int col) {
    if (index == strlen(word) - 1 && board[row][col] == word[index]) {
        return true;
    } else if (board[row][col] == word[index]) {
        char temp = board[row][col];
        board[row][col] = '#';

        if (row - 1 >= 0 && board[row - 1][col] != '#' && backtrack(board, board_size, board_col_size, word, index + 1, row - 1, col)) {
            return true;
        }
        if (col + 1 < board_col_size && board[row][col + 1] != '#' && backtrack(board, board_size, board_col_size, word, index + 1, row, col + 1)) {
            return true;
        }
        if (row + 1 < board_size && board[row + 1][col] != '#' && backtrack(board, board_size, board_col_size, word, index + 1, row + 1, col)) {
            return true;
        }
        if (col - 1 >= 0 && board[row][col - 1] != '#' && backtrack(board, board_size, board_col_size, word, index + 1, row, col - 1)) {
            return true;
        }

        board[row][col] = temp;
        return false;
    }
    return false;
}

bool exist(char** board, int board_size, int* board_col_size, char* word) {
    int len = strlen(word);
    if (len > board_size * *board_col_size) {
        return false;
    }

    int upper_board_counts[26] = {0};
    int lower_board_counts[26] = {0};
    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < *board_col_size; ++j) {
            if (board[i][j] >= 'A' && board[i][j] <= 'Z') {
                ++upper_board_counts[board[i][j] - 'A'];
            } else {
                ++lower_board_counts[board[i][j] - 'a'];
            }
        }
    }

    int upper_word_counts[26] = {0};
    int lower_word_counts[26] = {0};
    for (int i = 0; i < len; ++i) {
        if (word[i] >= 'A' && word[i] <= 'Z') {
            ++upper_word_counts[word[i] - 'A'];
        } else {
            ++lower_word_counts[word[i] - 'a'];
        }
    }

    for (int i = 0; i < 26; ++i) {
        if (upper_board_counts[i] < upper_word_counts[i] || lower_board_counts[i] < lower_word_counts[i]) {
            return false;
        }
    }

    char first = word[0];
    char last = word[len - 1];
    int first_freq = (first >= 'A' && first <= 'Z') ? upper_board_counts[first - 'A'] : lower_board_counts[first - 'a'];
    int last_freq = (last >= 'A' && last <= 'Z') ? upper_board_counts[last - 'A'] : lower_board_counts[last - 'a'];

    if (last_freq < first_freq) {
        for (int i = 0; i < len / 2; ++i) {
            char temp = word[i];
            word[i] = word[len - i - 1];
            word[len - i - 1] = temp;
        }
    }

    for (int row = 0; row < board_size; row++) {
        for (int col = 0; col < *board_col_size; col++) {
            if (board[row][col] == word[0] && backtrack(board, board_size, *board_col_size, word, 0, row, col)) {
                return true;
            }
        }
    }
    return false;
}
