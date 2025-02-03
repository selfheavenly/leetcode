#include <stdio.h>
#include <stdlib.h>

struct Tree_Node {
    int val;
    struct Tree_Node* left;
    struct Tree_Node* right;
};

void dfs(struct Tree_Node* node, int cur_max, int* count) {
    if (!node) return;

    if (node->val >= cur_max) {
        (*count)++;
        cur_max = node->val;
    }

    dfs(node->left, cur_max, count);
    dfs(node->right, cur_max, count);
}

int good_nodes(struct Tree_Node* root) {
    if (!root) return 0;
    
    int count = 0;
    dfs(root, root->val, &count);
    return count;
}
