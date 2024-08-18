#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nthUglyNumber(int n) {
    int retVal = 0;

    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[1] = 1;

    int idx2 = 1;
    int num2;
    int idx3 = 1;
    int num3;
    int idx5 = 1;
    int num5;
    int i;
    for (i = 2; i <= n; ++i) {
        num2 = dp[idx2] * 2;
        num3 = dp[idx3] * 3;
        num5 = dp[idx5] * 5;
        dp[i] = fmin(num2, fmin(num3, num5));

        if (dp[i] == num2) {
            idx2++;
        }
        if (dp[i] == num3) {
            idx3++;
        }
        if (dp[i] == num5) {
            idx5++;
        }
    }
    retVal = dp[n];

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{10}, {1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 10
     *  Output: 12
     *
     *  Input: n = 1
     *  Output: 1
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = nthUglyNumber(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
