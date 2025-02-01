#include <stdio.h>
#include <stdlib.h>

struct Tree_Node {
    int val;
    struct Tree_Node* left;
    struct Tree_Node* right;
};


int** levelOrder(struct Tree_Node* root, int* return_size, int** return_column_sizes) {
    if (root == NULL) {
        *return_size = 0;
        *return_column_sizes = NULL;
        return NULL;
    }

    struct Tree_Node* queue[2000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int** result = (int**)malloc(2000 * sizeof(int*));
    *return_column_sizes = (int*)malloc(2000 * sizeof(int));
    *return_size = 0;

    while (front < rear) {
        int level_size = rear - front;
        result[*return_size] = (int*)malloc(level_size * sizeof(int));
        (*return_column_sizes)[*return_size] = level_size;

        for (int i = 0; i < level_size; i++) {
            struct Tree_Node* node = queue[front++];
            result[*return_size][i] = node->val;

            if (node->left) queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }
        (*return_size)++;
    }

    return result;
}