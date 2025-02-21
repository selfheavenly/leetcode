#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    int num_neighbors;
    struct Node** neighbors;
} Node;

Node* clone_graph_dfs(Node* node, Node** cloned_nodes) {
    if (!node) return NULL;
    
    if (cloned_nodes[node->val]) {
        return cloned_nodes[node->val];
    }

    Node* clone = (Node*)malloc(sizeof(Node));
    clone->val = node->val;
    clone->num_neighbors = node->num_neighbors;
    clone->neighbors = (Node**)malloc(node->num_neighbors * sizeof(Node*));

    cloned_nodes[node->val] = clone;

    for (int i = 0; i < node->num_neighbors; i++) {
        clone->neighbors[i] = clone_graph_dfs(node->neighbors[i], cloned_nodes);
    }

    return clone;
}

Node* clone_graph(Node* node) {
    if (!node) return NULL;

    Node* cloned_nodes[101] = {NULL};
    return clone_graph_dfs(node, cloned_nodes);
}
