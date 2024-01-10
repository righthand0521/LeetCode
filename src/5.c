#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if (1)  // Dynamic Programming
char* longestPalindrome(char* s) {
    char* pRetVal = NULL;

    int returnStartIdx = 0;
    int returnSize = 0;

    /* Example: Input: s = "babad"
     *      0 1 2 3 4 |     0 1 2 3 4 |     0 1 2 3 4
     *      b a b a d |     b a b a d |     b a b a d
     *  0 b T         | 0 b T F       | 0 b T F T F F
     *  1 a   T       | 1 a   T F     | 1 a   T F T F
     *  2 b     T     | 2 b     T F   | 2 b     T F F
     *  3 a       T   | 3 a       T F | 3 a       T F
     *  4 d         T | 4 d         T | 4 d         T
     *
     * Example: Input: s = "cbbd"
     *      0 1 2 3 |     0 1 2 3 |     0 1 2 3
     *      c b b d |     c b b d |     c b b d
     *  0 c T       | 0 c T F     | 0 c T F F F
     *  1 b   T     | 1 b   T T   | 1 b   T T F
     *  2 b     T   | 2 b     T F | 2 b     T F
     *  3 d       T | 3 d       T | 3 d       T
     */
    int sSize = strlen(s);
    int dpSize = sSize;
    int dp[dpSize][dpSize];
    memset(dp, 0, sizeof(dp));
    int i, j;
    //
    for (i = 0; i < dpSize; ++i) {
        dp[i][i] = 1;
        returnStartIdx = i;
        returnSize = i - i + 1;
    }
    //
    for (i = 0; i < sSize - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = 1;
            returnStartIdx = i;
            returnSize = (i + 1) - i + 1;
        }
    }
    //
    int diff;
    for (diff = 2; diff < sSize; ++diff) {
        for (i = 0; i < sSize - diff; ++i) {
            j = i + diff;
            if ((s[i] == s[j]) && (dp[i + 1][j - 1] == 1)) {
                dp[i][j] = 1;
                returnStartIdx = i;
                returnSize = j - i + 1;
            }
        }
    }
    //
    s[returnStartIdx + returnSize] = '\0';
    pRetVal = s + returnStartIdx;

    return pRetVal;
}
#else
char* longestPalindrome(char* s) {
    char* pRetVal = NULL;

    int len = strlen(s);
    int start = 0;
    int subLen = 0;
    int left, right;
    int i;

    // odd
    for (i = 0; i < len; ++i) {
        left = i - 1;
        right = i + 1;
        while ((left >= 0) && (right < len) && (s[left] == s[right])) {
            --left;
            ++right;
        }

        if (right - left - 1 > subLen) {
            start = left + 1;
            subLen = right - left - 1;
        }
    }

    // even
    for (int i = 0; i < len; i++) {
        left = i;
        right = i + 1;
        while ((left >= 0) && (right < len) && (s[left] == s[right])) {
            --left;
            ++right;
        }

        if (right - left - 1 > subLen) {
            start = left + 1;
            subLen = right - left - 1;
        }
    }

    s[start + subLen] = '\0';
    pRetVal = s + start;

    return pRetVal;
}
#endif

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"babad"}, {"cbbd"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "babad"
     *  Output: "bab"
     *
     *  Input: s = "cbbd"
     *  Output: "bb"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = longestPalindrome(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
