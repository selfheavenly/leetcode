#include <stdlib.h>

int maxSubArray(int *nums, int nums_size) {
    int max_sum = nums[0], current_sum = 0;
    for (int i = 0; i < nums_size; i++) {
        current_sum += nums[i];
        if (current_sum > max_sum) max_sum = current_sum;
        if (current_sum < 0) current_sum = 0;
    }
    return max_sum;
}
