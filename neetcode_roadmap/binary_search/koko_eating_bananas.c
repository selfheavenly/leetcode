#include <stdlib.h>

int can_eat_em(int* piles, int piles_size, int k, int hours) {
    long actual = 0;
    for (int i = 0; i < piles_size; i++) {
        actual += (piles[i] + k - 1) / k;
    }
    return (actual <= hours);
}

int minEatingSpeed(int* piles, int piles_size, int h) {
    int left = 1, mid, right = piles[0];

    for (int i = 0; i < piles_size; i++) {
        if (piles[i] > right) right = piles[i];
    }

    while (left < right) {
        mid = (left + right) >> 1;
        if (can_eat_em(piles, piles_size, mid, h)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return right;
}