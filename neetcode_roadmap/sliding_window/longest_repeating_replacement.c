#include <stdlib.h>

int characterReplacement(char* s, int k) {
    int n = strlen(s);
    int count[26] = {0};
    int max_freq = 0;
    int start = 0;
    int max_length = 0;

    for (int end = 0; end < n; end++) {
        count[s[end] - 'A']++;
        
        if (count[s[end] - 'A'] > max_freq) {
            max_freq = count[s[end] - 'A'];
        }

        while ((end - start + 1) - max_freq > k) {
            count[s[start] - 'A']--;
            start++;
        }

        max_length = (end - start + 1 > max_length) ? end - start + 1 : max_length;
    }

    return max_length;
}