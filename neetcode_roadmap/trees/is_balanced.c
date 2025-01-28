#include <stdlib.h>
#include <stdbool.h>

struct Tree_Node {
    int val;
    struct Tree_Node* left;
    struct Tree_Node* right;
};

int check_height(struct Tree_Node* root) {
    if (root == NULL) {
        return 0;
    }

    int left_height = check_height(root->left);
    if (left_height == -1) return -1;

    int right_height = check_height(root->right);
    if (right_height == -1) return -1;

    if (abs(left_height - right_height) > 1) {
        return -1;
    }

    return (left_height > right_height ? left_height : right_height) + 1;
}

bool is_balanced(struct Tree_Node* root) {
    return check_height(root) != -1;
}