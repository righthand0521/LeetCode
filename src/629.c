#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int kInversePairs(int n, int k) {
    int retVal = 0;

    int dp[k + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    int dpCurrent[k + 1];
    int i, j;
    for (i = 1; i < (n + 1); ++i) {
        memset(dpCurrent, 0, sizeof(dpCurrent));
        for (j = 0; j < (k + 1); ++j) {
            dpCurrent[j] = 0;
            if (j - 1 >= 0) {
                dpCurrent[j] = dpCurrent[j - 1];
            }
            if (j - i >= 0) {
                dpCurrent[j] -= dp[j - i];
                if (dpCurrent[j] < 0) {
                    dpCurrent[j] += MODULO;
                }
            }
            dpCurrent[j] = (dpCurrent[j] + dp[j]) % MODULO;
        }
        memcpy(dp, dpCurrent, sizeof(dp));
    }
    retVal = dp[k];

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int k;
    } testCase[] = {{3, 0}, {3, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, k = 0
     *  Output: 1
     *
     *  Input: n = 3, k = 1
     *  Output: 2
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d\n", testCase[i].n, testCase[i].k);

        answer = kInversePairs(testCase[i].n, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
