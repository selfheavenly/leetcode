#include <stdlib.h>

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize == 0) return 0;
    int min = prices[0];
    int max = 0;
    for (int i = 1; i < pricesSize; ++i) {
        int diff = prices[i] - min;
        if (diff > max)
            max = diff;
        if (prices[i] < min)
            min = prices[i];
    }
    return max;
}