#include <stdio.h>

int house_robber(int* nums, int nums_size) {
    if (nums_size == 1) return nums[0];
    int prev2 = 0, prev1 = 0, curr;
    for (int i = 0; i < nums_size; i++) {
        curr = (prev2 + nums[i] > prev1) ? prev2 + nums[i] : prev1;
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}