#include <stdbool.h>

bool can_jump(int* nums, int nums_size) {
    int max_reach = 0;
    
    for (int i = 0; i < nums_size; i++) {
        if (i > max_reach) return false;
        max_reach = (i + nums[i] > max_reach) ? (i + nums[i]) : max_reach;
        if (max_reach >= nums_size - 1) return true;
    }
    
    return false;
}
