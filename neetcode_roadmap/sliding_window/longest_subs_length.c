#include <stdlib.h>

int lengthOfLongestSubstring(char* s) {
    int n = strlen(s);
    int max_length = 0;
    int start = 0;
    int last_seen[128];
    
    for (int i = 0; i < 128; i++) {
        last_seen[i] = -1;
    }
    
    for (int end = 0; end < n; end++) {
        char current_char = s[end];
        
        if (last_seen[current_char] >= start) {
            start = last_seen[current_char] + 1;
        }
        
        last_seen[current_char] = end;
        max_length = (end - start + 1 > max_length) ? end - start + 1 : max_length;
    }
    
    return max_length;
}