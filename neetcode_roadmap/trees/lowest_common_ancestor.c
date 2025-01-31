#include <stdio.h>
#include <stdlib.h>

struct Tree_Node {
    int val;
    struct Tree_Node* left;
    struct Tree_Node* right;
};

struct Tree_Node* lowest_common_ancestor(struct Tree_Node* root, struct Tree_Node* p, struct Tree_Node* q) {
    if (root == NULL) return NULL;

    if (p->val < root->val && q->val < root->val) {
        return lowest_common_ancestor(root->left, p, q);
    }
    
    if (p->val > root->val && q->val > root->val) {
        return lowest_common_ancestor(root->right, p, q);
    }
    
    return root;
}