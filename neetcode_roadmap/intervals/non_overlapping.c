#include <stdlib.h>

int compare_intervals(const void *a, const void *b) {
    return (*(int **)a)[1] - (*(int **)b)[1];
}

int erase_overlap_intervals(int **intervals, int intervals_size, int *intervals_col_size) {
    if (intervals_size == 0) return 0;

    qsort(intervals, intervals_size, sizeof(int *), compare_intervals);

    int end = intervals[0][1];
    int removed = 0;

    for (int i = 1; i < intervals_size; i++) {
        if (intervals[i][0] < end) {
            removed++;
        } else {
            end = intervals[i][1];
        }
    }

    return removed;
}
