#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LETTERS_SIZE (26)  // s consists of only lowercase English letters.
int countPalindromicSubsequence(char* s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i, j;

    int left[LETTERS_SIZE];
    int right[LETTERS_SIZE];
    for (i = 0; i < LETTERS_SIZE; ++i) {
        left[i] = -1;
        right[i] = -1;
    }

    int idx;
    for (i = 0; i < sSize; ++i) {
        idx = s[i] - 'a';
        if (left[idx] == -1) {
            left[idx] = i;
        }
        right[idx] = i;
    }

    int betweenCount;
    int between[LETTERS_SIZE];
    for (i = 0; i < LETTERS_SIZE; ++i) {
        if (left[i] == -1) {
            continue;
        }

        betweenCount = 0;
        memset(between, 0, sizeof(between));
        for (j = left[i] + 1; j < right[i]; ++j) {
            idx = s[j] - 'a';
            if (between[idx] == 0) {
                between[idx]++;
                betweenCount++;
            }
        }
        retVal += betweenCount;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aabca"}, {"adc"}, {"bbcbaba"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aabca"
     *  Output: 3
     *
     *  Input: s = "adc"
     *  Output: 0
     *
     *  Input: s = "bbcbaba"
     *  Output: 4
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = countPalindromicSubsequence(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
