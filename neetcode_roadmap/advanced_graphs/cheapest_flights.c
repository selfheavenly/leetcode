#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_cheapest_price(int n, int **flights, int flights_size, int *flights_col_size, 
                        int src, int dst, int k) {
    int *cost = (int *)malloc(n * sizeof(int));
    int *temp = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) 
        cost[i] = INT_MAX;
    
    cost[src] = 0;

    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < n; j++) 
            temp[j] = cost[j];

        for (int j = 0; j < flights_size; j++) {
            int u = flights[j][0], v = flights[j][1], price = flights[j][2];
            if (cost[u] != INT_MAX && cost[u] + price < temp[v]) 
                temp[v] = cost[u] + price;
        }
        int *swap = cost;
        cost = temp;
        temp = swap;
    }

    int result = (cost[dst] == INT_MAX) ? -1 : cost[dst];
    free(cost);
    free(temp);
    return result;
}
