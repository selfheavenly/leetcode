#include <stdbool.h>

bool isAnagram(char* s, char* t) {
    if (strlen(s) != strlen(t)) return false;

    int chars[26] = {0};

    for (int i = 0; s[i] != '\0'; i++) {
        chars[s[i] - 97] += 1;
        chars[t[i] - 97] -= 1;
    }

    for (int i = 0; i < 26; i++) { 
        if (chars[i] != 0) return false;
    }

    return true;
}