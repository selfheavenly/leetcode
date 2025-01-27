#include <stdio.h>
#include <stdlib.h>

struct Tree_Node {
    int val;
    struct Tree_Node* left;
    struct Tree_Node* right;
};

int calculate_diameter(struct Tree_Node* root, int* diameter) {
    if (root == NULL) {
        return 0;
    }

    int left_height = calculate_diameter(root->left, diameter);
    int right_height = calculate_diameter(root->right, diameter);

    *diameter = (left_height + right_height) > *diameter ? (left_height + right_height) : *diameter;

    return left_height > right_height ? left_height + 1 : right_height + 1;
}

int bin_tree_diameter(struct Tree_Node* root) {
    int diameter = 0;
    calculate_diameter(root, &diameter);
    return diameter;
}