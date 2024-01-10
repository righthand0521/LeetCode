#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.com/problems/new-21-game/solutions/132334/one-pass-dp-o-n/
double new21Game(int n, int k, int maxPts) {
    double retVal = 1;

    if ((k == 0) || (n >= k + maxPts)) {
        return retVal;
    }

    // dp[i] is the probability that we get points i at some moment.
    // 1 - dp[i]is the probability that we skip the points i.
    double dp[n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1.0;

    // maxPtsSum = sum(last maxPts dp values)
    double maxPtsSum = 1.0;

    // dp[i] = sum(last W dp values) / maxPts
    retVal = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = maxPtsSum / maxPts;
        if (i < k) {
            maxPtsSum += dp[i];
        } else {
            retVal += dp[i];
        }

        if (i - maxPts >= 0) {
            maxPtsSum -= dp[i - maxPts];
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int k;
        int maxPts;
    } testCase[] = {{10, 1, 10}, {6, 1, 10}, {21, 17, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 10, k = 1, maxPts = 10
     *  Output: 1.00000
     *
     *  Input: n = 6, k = 1, maxPts = 10
     *  Output: 0.60000
     *
     *  Input: n = 21, k = 17, maxPts = 10
     *  Output: 0.73278
     */

    int i;
    double answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d, maxPts = %d\n", testCase[i].n, testCase[i].k, testCase[i].maxPts);

        answer = new21Game(testCase[i].n, testCase[i].k, testCase[i].maxPts);
        printf("Output: %.5f\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
