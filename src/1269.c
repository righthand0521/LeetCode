#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int numWays(int steps, int arrLen) {
    int retVal = 0;

    // dp[step][index] : 0 <= step <= steps, 0 <= index <= arrLen - 1.
    // => dp[step][index] : 0 <= step <= steps, 0 <= index <= min(arrLen - 1, steps).
    // => dpNextStep[index], 0 <= index <= min(arrLen - 1, steps).
    int maxIndex = fmin(arrLen - 1, steps);
    int dp[maxIndex + 1];
    memset(dp, 0, sizeof(dp));
    int dpNextStep[maxIndex + 1];
    dp[0] = 1;
    for (int i = 1; i <= steps; ++i) {
        memset(dpNextStep, 0, sizeof(dpNextStep));
        for (int j = 0; j <= maxIndex; ++j) {
            dpNextStep[j] = dp[j];
            if (j - 1 >= 0) {
                dpNextStep[j] = (dpNextStep[j] + dp[j - 1]) % MODULO;
            }
            if (j + 1 <= maxIndex) {
                dpNextStep[j] = (dpNextStep[j] + dp[j + 1]) % MODULO;
            }
        }
        memcpy(dp, dpNextStep, sizeof(dp));
    }
    retVal = dp[0];

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int steps;
        int arrLen;
    } testCase[] = {{3, 2}, {2, 4}, {4, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: steps = 3, arrLen = 2
     *  Output: 4
     *
     *  Input: steps = 2, arrLen = 4
     *  Output: 2
     *
     *  Input: steps = 4, arrLen = 2
     *  Output: 8
     */

    int pAnswer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: steps = %d, arrLen = %d\n", testCase[i].steps, testCase[i].arrLen);

        pAnswer = numWays(testCase[i].steps, testCase[i].arrLen);
        printf("Output: %d\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
