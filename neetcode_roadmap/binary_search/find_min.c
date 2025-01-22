#include <stdlib.h>

int find_min(int* nums, int nums_size) {
    int left = 0, right = nums_size - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] <= nums[right]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return nums[left];
}