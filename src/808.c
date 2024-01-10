#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
double soupServings(int n) {
    double retVal = 1;

    /* Answers within 10 ^ -5 of the actual answer will be accepted.
     *  E(A) = (4 + 3 + 2 + 1) x 0.25 = 2.5
     *  E(B) = (0 + 1 + 2 + 3) x 0.25 = 1.5
     *
     *  n = 4475, p ≈ 0.999990211307
     *  n = 4476, p ≈ 0.999990468596
     *
     *  n ≥ 179 x 25
     */
    n = ceil((double)n / 25);
    if (n >= 179) {
        return retVal;
    }

    // https://leetcode.cn/problems/soup-servings/solutions/1982919/by-joneli-ts7a/
    double dp[n + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 0.5;
    int i, j;
    for (i = 1; i <= n; i++) {
        dp[0][i] = 1.0;
    }
    double sum;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            sum = 0;
            sum += dp[MAX(0, i - 4)][j];
            sum += dp[MAX(0, i - 3)][MAX(0, j - 1)];
            sum += dp[MAX(0, i - 2)][MAX(0, j - 2)];
            sum += dp[MAX(0, i - 1)][MAX(0, j - 3)];
            dp[i][j] = sum / 4.0;
        }
    }
    retVal = dp[n][n];

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{50}, {100}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 50
     *  Output: 0.62500
     *
     *  Input: n = 100
     *  Output: 0.71875
     */

    double answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = soupServings(testCase[i].n);
        printf("Output: %.5f\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
