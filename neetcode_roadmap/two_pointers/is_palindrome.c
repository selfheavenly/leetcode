#include <stdbool.h>
#include <stdlib.h>

bool isPalindrome(char* s) {
    int left = 0;
    int right = strlen(s) - 1;

    while (left < right) {
        // I. Skip non-alphanumeric characters from the left
        while (left < right && !isalnum(s[left])) {
            left++;
        }

        // II. Skip non-alphanumeric characters from the right
        while (left < right && !isalnum(s[right])) {
            right--;
        }

        // III. Compare the lowercase left character with the right one
        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}