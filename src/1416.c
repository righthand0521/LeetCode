#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int numberOfArrays(char *s, int k) {
    int retVal = 0;

    int sSize = strlen(s);

    // dp[i] is the number of ways you can divide the string starting from index i to the end.
    int dp[sSize + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    long long num;
    int i, j;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == '0') {
            continue;
        }

        num = s[i] - '0';
        for (j = (i + 1); j < (sSize + 1); ++j) {
            if (num > (long long)k) {
                break;
            }
            num *= 10;
            num += s[j] - '0';

            dp[j] += dp[i];
            dp[j] %= MODULO;
        }

        dp[i] %= MODULO;
    }
    retVal = dp[sSize] % MODULO;

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        char *s;
        int k;
    } testCase[] = {{"1000", 10000}, {"1000", 10}, {"1317", 2000}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "1000", k = 10000
     *  Output: 1
     *
     *  Input: s = "1000", k = 10
     *  Output: 0
     *
     *  Input: s = "1317", k = 2000
     *  Output: 8
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        answer = numberOfArrays(testCase[i].s, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
