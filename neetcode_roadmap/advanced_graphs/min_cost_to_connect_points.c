#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_cost_connect_points(int **points, int n, int *col_size) {
    int *min_dist = (int *)malloc(n * sizeof(int));
    char *visited = (char *)calloc(n, sizeof(char));
    int total_cost = 0, edges_used = 0, curr = 0;

    for (int i = 1; i < n; i++) 
        min_dist[i] = INT_MAX;

    while (++edges_used < n) {
        visited[curr] = 1;
        int next = -1, min_edge = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int dist = abs(points[curr][0] - points[i][0]) + 
                           abs(points[curr][1] - points[i][1]);
                if (dist < min_dist[i]) 
                    min_dist[i] = dist;

                if (min_dist[i] < min_edge) {
                    min_edge = min_dist[i];
                    next = i;
                }
            }
        }
        total_cost += min_edge;
        curr = next;
    }

    free(min_dist);
    free(visited);
    return total_cost;
}
