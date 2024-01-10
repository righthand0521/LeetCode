#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestPalindromeSubseq(char* s) {
    int retVal = 0;

    /* dp[i][j]: the longest palindromic subsequence's length of substring(i, j)
     *  +-----------------------+   +-------------------+
     *  |   | b | b | b | a | b |   |   | c | b | b | d |
     *  |---+---+---+---+---+---|   |---+---+---+---+---|
     *  | b | 1 | 2 | 3 | 3 |[4]|   | c | 1 | 1 | 2 |[2]|
     *  |---+---+---+---+---+---|   |---+---+---+---+---|
     *  | b | 0 | 1 | 2 | 2 | 3 |   | b | 0 | 1 | 2 | 2 |
     *  |---+---+---+---+---+---|   |---+---+---+---+---|
     *  | b | 0 | 0 | 1 | 1 | 3 |   | b | 0 | 0 | 1 | 1 |
     *  |---+---+---+---+---+---|   |---+---+---+---+---|
     *  | a | 0 | 0 | 0 | 1 | 1 |   | d | 0 | 0 | 0 | 1 |
     *  |---+---+---+---+---+---|   +-------------------+
     *  | b | 0 | 0 | 0 | 0 | 1 |
     *  +-----------------------+
     */
    int sSize = strlen(s);
    int dp[sSize][sSize];
    memset(dp, 0, sizeof(dp));
    int i, j;
    for (i = sSize - 1; i >= 0; i--) {
        dp[i][i] = 1;
        for (j = i + 1; j < sSize; j++) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = fmax(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    retVal = dp[0][sSize - 1];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"bbbab"}, {"cbbd"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "bbbab"
     *  Output: 4
     *
     *  Input: s = "cbbd"
     *  Output: 2
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = longestPalindromeSubseq(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
