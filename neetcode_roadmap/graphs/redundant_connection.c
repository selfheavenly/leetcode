#include <stdlib.h>

typedef struct {
    int *parent;
    int *rank;
} UnionFind;

UnionFind* union_find_create(int n) {
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    uf->parent = (int*)malloc(n * sizeof(int));
    uf->rank = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        uf->parent[i] = i;
    }
    return uf;
}

int find(UnionFind* uf, int x) {
    if (uf->parent[x] != x) {
        uf->parent[x] = find(uf, uf->parent[x]);
    }
    return uf->parent[x];
}

int union_sets(UnionFind* uf, int x, int y) {
    int root_x = find(uf, x);
    int root_y = find(uf, y);
    
    if (root_x == root_y) return 0;
    
    if (uf->rank[root_x] > uf->rank[root_y]) {
        uf->parent[root_y] = root_x;
    } else if (uf->rank[root_x] < uf->rank[root_y]) {
        uf->parent[root_x] = root_y;
    } else {
        uf->parent[root_y] = root_x;
        uf->rank[root_x]++;
    }
    
    return 1;
}

int* find_redundant_connection(int** edges, int edges_size, int* edges_col_size, int* return_size) {
    int* result = (int*)malloc(2 * sizeof(int));
    *return_size = 2;

    UnionFind* uf = union_find_create(edges_size + 1);

    for (int i = 0; i < edges_size; i++) {
        if (!union_sets(uf, edges[i][0], edges[i][1])) {
            result[0] = edges[i][0];
            result[1] = edges[i][1];
        }
    }

    free(uf->parent);
    free(uf->rank);
    free(uf);
    
    return result;
}
