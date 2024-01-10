#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minInsertions(char *s) {
    int retVal = 0;

    int sSize = strlen(s);
    int dp[sSize + 1][sSize + 1];
    memset(dp, 0, sizeof(dp));

    int i, j;
    char sReverse[sSize + 1];
    memset(sReverse, 0, sizeof(sReverse));
    for (i = 0; i < sSize; ++i) {
        sReverse[sSize - 1 - i] = s[i];
    }
    for (i = 1; i <= sSize; ++i) {
        for (j = 1; j <= sSize; ++j) {
            dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]);
            if (s[i - 1] == sReverse[j - 1]) {
                dp[i][j] = fmax(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    retVal = sSize - dp[sSize][sSize];

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        char *s;
    } testCase[] = {{"zzazz"}, {"mbadm"}, {"leetcode"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "zzazz"
     *  Output: 0
     *
     *  Input: s = "mbadm"
     *  Output: 2
     *
     *  Input: s = "leetcode"
     *  Output: 5
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minInsertions(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
