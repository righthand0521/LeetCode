#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int numRollsToTarget(int n, int k, int target) {
    int retVal = 0;

    /* dp[n][target] = dp[n-1][target-x], x = 1, .., k
     *    0 1 2 3 4 5 6 7
     *  0 1 0 0 0 0 0 0 0
     *  1 0 1 1 1 1 1 1 0
     *  2 0 0 1 2 3 4 5 6
     */
    int dp[n + 1][target + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    long long sum;
    int i, j, x;
    for (i = 1; i < (n + 1); ++i) {
        for (j = 1; j < (target + 1); ++j) {
            for (x = 1; x < (k + 1); ++x) {
                if (j - x >= 0) {
                    sum = dp[i][j] + dp[i - 1][j - x];
                    dp[i][j] = sum % MODULO;
                }
            }
        }
    }
    retVal = dp[n][target];

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
        int k;
        int target;
    } testCase[] = {{1, 6, 3}, {2, 6, 7}, {30, 30, 500}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1, k = 6, target = 3
     *  Output: 1
     *
     *  Input: n = 2, k = 6, target = 7
     *  Output: 6
     *
     *  Input: n = 30, k = 30, target = 500
     *  Output: 222616187
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d, target = %d\n", testCase[i].n, testCase[i].k, testCase[i].target);

        answer = numRollsToTarget(testCase[i].n, testCase[i].k, testCase[i].target);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
