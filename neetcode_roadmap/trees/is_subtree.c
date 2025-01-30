#include <stdbool.h>
#include <stdlib.h>

struct Tree_Node {
    int val;
    struct Tree_Node* left;
    struct Tree_Node* right;
};

bool is_same_tree(struct Tree_Node* p, struct Tree_Node* q) {
    if (p == NULL && q == NULL) return true;
    if (p == NULL || q == NULL) return false;
    if (p->val != q->val) return false;

    return is_same_tree(p->left, q->left) && is_same_tree(p->right, q->right);
}

bool is_subtree(struct Tree_Node* root, struct Tree_Node* sub_root) {
    if (root == NULL) return false;

    if (is_same_tree(root, sub_root)) return true;

    return is_subtree(root->left, sub_root) || is_subtree(root->right, sub_root);
}
