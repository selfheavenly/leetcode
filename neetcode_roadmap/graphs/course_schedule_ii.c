#include <stdlib.h>
#include <stdbool.h>

int* find_order(int num_courses, int** prerequisites, int prerequisites_size, int* prerequisites_col_size, int* return_size) {
    int** adj = (int**)malloc(num_courses * sizeof(int*));
    int* adj_size = (int*)calloc(num_courses, sizeof(int));
    int* in_degree = (int*)calloc(num_courses, sizeof(int));
    
    for (int i = 0; i < prerequisites_size; i++) {
        int b = prerequisites[i][1];
        adj_size[b]++;
    }
    
    for (int i = 0; i < num_courses; i++) {
        adj[i] = (int*)malloc(adj_size[i] * sizeof(int));
        adj_size[i] = 0;
    }
    
    for (int i = 0; i < prerequisites_size; i++) {
        int a = prerequisites[i][0];
        int b = prerequisites[i][1];
        adj[b][adj_size[b]++] = a;
        in_degree[a]++;
    }
    
    int* queue = (int*)malloc(num_courses * sizeof(int));
    int front = 0, rear = 0;
    for (int i = 0; i < num_courses; i++) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }
    
    int* result = (int*)malloc(num_courses * sizeof(int));
    int count = 0;
    
    while (front < rear) {
        int u = queue[front++];
        result[count++] = u;
        for (int i = 0; i < adj_size[u]; i++) {
            int v = adj[u][i];
            if (--in_degree[v] == 0) {
                queue[rear++] = v;
            }
        }
    }
    
    for (int i = 0; i < num_courses; i++) {
        free(adj[i]);
    }
    free(adj);
    free(adj_size);
    free(in_degree);
    free(queue);
    
    if (count == num_courses) {
        *return_size = num_courses;
        return result;
    } else {
        *return_size = 0;
        free(result);
        return NULL;
    }
}
