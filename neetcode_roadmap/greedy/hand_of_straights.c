#include <stdlib.h>
#include <stdbool.h>

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int same(int *h, int hs, int i) {
    if (i >= hs) return i;
    int j = i + 1;
    while (j < hs && h[j] == h[i]) j++;
    return j;
}

bool is_n_straight_hand(int *hand, int hand_size, int group_size) {
    int *h = hand, hs = hand_size, gs = group_size, i = 0, j, k = 0, m, p, q;
    if (hs % gs != 0) return false;
    qsort(h, hs, sizeof(int), cmp);
    int *a = (int *)malloc(gs * sizeof(int));
    if (!a) return false;
    while (i < hs) {
        p = i;
        for (j = k; j < gs; j++) {
            if (p >= hs) {
                free(a);
                return false;
            }
            if (j != 0 && h[p] != h[p - 1] + 1) {
                free(a);
                return false;
            }
            q = same(h, hs, p);
            a[j] = q - p;
            p = q;
        }
        m = a[0];
        for (j = 0; j < gs; j++) {
            a[j] -= m;
            if (a[j] < 0) {
                free(a);
                return false;
            }
        }
        for (j = 1; j < gs; j++) {
            if (a[j] > 0) {
                if (q == hs) {
                    free(a);
                    return false;
                }
                for (i = j; i < gs; i++) a[i - j] = a[i];
                k = i - j;
                i = q;
                break;
            }
        }
        if (j == gs) {
            k = 0;
            i = q;
        }
    }
    free(a);
    return true;
}
