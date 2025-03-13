#include <stdio.h>

int min_cost_climbing_stairs(int* cost, int cost_size) {
    int prev1 = 0, prev2 = 0, curr;
    for (int i = 2; i <= cost_size; i++) {
        curr = (prev1 + cost[i - 1] < prev2 + cost[i - 2]) ? prev1 + cost[i - 1] : prev2 + cost[i - 2];
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}