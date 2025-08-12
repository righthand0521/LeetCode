#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)  // Since the answer can be very large, return it modulo 10^9 + 7.
int numberOfWays(int n, int x) {
    int retVal = 0;

    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        int val = (int)pow(i, x);
        if (val > n) {
            break;
        }

        for (int j = n; j >= val; j--) {
            dp[j] = (dp[j] + dp[j - val]) % MODULO;
        }
    }
    retVal = dp[n];

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int x;
    } testCase[] = {{10, 2}, {4, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 10, x = 2
     *  Output: 1
     *
     *  Input: n = 4, x = 1
     *  Output: 2
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, x = %d\n", testCase[i].n, testCase[i].x);

        answer = numberOfWays(testCase[i].n, testCase[i].x);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
