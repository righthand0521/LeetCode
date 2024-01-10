#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int countGoodStrings(int low, int high, int zero, int one) {
    int retVal = 0;

    int dp[high + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    int i;
    for (i = 1; i <= high; ++i) {
        if (i >= zero) {
            dp[i] += dp[i - zero];
            dp[i] %= MODULO;
        }

        if (i >= one) {
            dp[i] += dp[i - one];
            dp[i] %= MODULO;
        }
    }

    for (i = low; i <= high; ++i) {
        retVal += dp[i];
        retVal %= MODULO;
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int low;
        int high;
        int zero;
        int one;
    } testCase[] = {{3, 3, 1, 1}, {2, 3, 1, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: low = 3, high = 3, zero = 1, one = 1
     *  Output: 8
     *
     *  Input: low = 2, high = 3, zero = 1, one = 2
     *  Output: 5
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: low = %d, high = %d, zero = %d, one = %d\n", testCase[i].low, testCase[i].zero, testCase[i].low,
               testCase[i].one);

        answer = countGoodStrings(testCase[i].low, testCase[i].high, testCase[i].zero, testCase[i].one);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
