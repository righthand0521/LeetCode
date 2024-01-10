#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strangePrinter(char *s) {
    int retVal = 0;

    /* https://leetcode.cn/problems/strange-printer/solutions/792309/xin-shou-pian-cong-xiao-wen-ti-zai-dao-q-qifh/
     *  s[i] == s[i]: dp[i][j] = dp[i][j-1]
     *  s[i] != s[j]: dp[i][j] = min(dp[i][i] + dp[i+1][j], dp[i][i+1] + dp[i+1][j], ..., dp[i][j-1] + dp[j-1][j])
     *
     *  Example: Input: s = "abab", Output: 3.
     *      0 1 2 3 |   0 1 2 3 |   0 1 2 3 |   0 1 2 3 |   0 1 2 3
     *      a b a b |   a b a b |   a b a b |   a b a b |   a b a b    dp[0][0] + dp[1][3] = 1 + 2 = 3
     *  0 a 0 0 0 0 | a 1 0 0 0 | a 1 2 0 0 | a 1 2 2 0 | a 1 2 2 3 -> dp[0][1] + dp[2][3] = 2 + 2 = 4
     *  1 b 0 0 0 0 | b 0 1 0 0 | b 0 1 2 0 | b 0 1 2 2 | b 0 1 2 2    dp[0][2] + dp[3][3] = 2 + 1 = 3
     *  2 a 0 0 0 0 | a 0 0 1 0 | a 0 0 1 2 | a 0 0 1 2 | a 0 0 1 2
     *  3 b 0 0 0 0 | b 0 0 0 1 | b 0 0 0 1 | b 0 0 0 1 | b 0 0 0 1
     */
    int sSize = strlen(s);
    int dp[sSize][sSize];
    memset(dp, 0, sizeof(dp));

    int minValue;
    int i, j, k;
    for (i = sSize - 1; i >= 0; --i) {
        dp[i][i] = 1;
        for (j = i + 1; j < sSize; ++j) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i][j - 1];
            } else {
                minValue = INT_MAX;
                for (k = i; k < j; ++k) {
                    minValue = fmin(minValue, dp[i][k] + dp[k + 1][j]);
                }
                dp[i][j] = minValue;
            }
        }
    }
#if (0)
    for (i = 0; i < sSize; ++i) {
        for (j = 0; j < sSize; ++j) {
            printf("%2d", dp[i][j]);
        }
        printf("\n");
    }
#endif
    retVal = dp[0][sSize - 1];

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aaabbb"}, {"aba"}, {"abab"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aaabbb"
     *  Output: 2
     *
     *  Input: s = "aba"
     *  Output: 2
     *
     *  Input: s = "abab"
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = strangePrinter(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
