#include <stdio.h>
#include <stdlib.h>

struct Tree_Node {
    int val;
    struct Tree_Node* left;
    struct Tree_Node* right;
};

int* right_side_view(struct Tree_Node* root, int* return_size) {
    if (root == NULL) {
        *return_size = 0;
        return NULL;
    }

    struct Tree_Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int* result = (int*)malloc(100 * sizeof(int));
    *return_size = 0;

    while (front < rear) {
        int level_size = rear - front;
        struct Tree_Node* last_node = NULL;

        for (int i = 0; i < level_size; i++) {
            struct Tree_Node* node = queue[front++];
            last_node = node;

            if (node->left) queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }

        result[(*return_size)++] = last_node->val;
    }

    return result;
}