#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS_SIZE (3)  // s consists of only the letters 'a', 'b', and 'c'.
int takeCharacters(char* s, int k) {
    int retVal = -1;

    int sSize = strlen(s);
    int i;

    // Count total occurrences
    int count[MAX_LETTERS_SIZE];
    memset(count, 0, sizeof(count));
    for (i = 0; i < sSize; ++i) {
        count[s[i] - 'a']++;
    }

    // Check if we have enough characters
    for (i = 0; i < MAX_LETTERS_SIZE; i++) {
        if (count[i] < k) {
            return retVal;
        }
    }

    // Find the longest window that leaves k of each character outside
    int window[MAX_LETTERS_SIZE];
    memset(window, 0, sizeof(window));
    int maxWindow = 0;
    int left = 0;
    int right = 0;
    for (right = 0; right < sSize; right++) {
        window[s[right] - 'a']++;

        // Shrink window if we take too many characters
        while ((left <= right) &&
               ((count[0] - window[0] < k) || (count[1] - window[1] < k) || (count[2] - window[2] < k))) {
            window[s[left] - 'a']--;
            left++;
        }

        maxWindow = fmax(maxWindow, right - left + 1);
    }

    retVal = sSize - maxWindow;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        int k;
    } testCase[] = {{"aabaaaacaabc", 2}, {"a", 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aabaaaacaabc", k = 2
     *  Output: 8
     *
     *  Input: s = "a", k = 1
     *  Output: -1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        answer = takeCharacters(testCase[i].s, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
