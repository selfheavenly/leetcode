#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* partition_labels(char* s, int* return_size) {
    int last_index[26] = {0};
    int length = strlen(s);
    
    for (int i = 0; i < length; i++) {
        last_index[s[i] - 'a'] = i;
    }
    
    int* result = (int*)malloc(length * sizeof(int));
    *return_size = 0;
    
    int start = 0, end = 0;
    
    for (int i = 0; i < length; i++) {
        if (last_index[s[i] - 'a'] > end) {
            end = last_index[s[i] - 'a'];
        }
        
        if (i == end) {
            result[(*return_size)++] = end - start + 1;
            start = i + 1;
        }
    }
    
    return result;
}
