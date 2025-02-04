#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct Tree_Node {
    int val;
    struct Tree_Node* left;
    struct Tree_Node* right;
};

bool dfs(struct Tree_Node* root, long min_value, long max_value) {
    if (root == NULL) return true;
    if (root -> val <= min_value || root -> val >= max_value) return false;
    return dfs(root -> left, min_value, root -> val) && dfs(root -> right, root -> val, max_value);
}

bool isValidBST(struct Tree_Node* root) {
    return dfs(root, LONG_MIN, LONG_MAX);
}
