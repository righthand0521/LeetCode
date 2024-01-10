#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minTaps(int n, int* ranges, int rangesSize) {
    int retVal = -1;

    int i, j;

    // 1 <= n <= 10^4; ranges.length == n + 1; 0 <= ranges[i] <= 100
    int infinity = (int)(1e9);

    int dpSize = n + 1;
    int dp[dpSize];
    memset(dp, 0, sizeof(dp));
    dp[0] = 0;
    for (i = 1; i < dpSize; ++i) {
        dp[i] = infinity;
    }

    int tapStart, tapEnd;
    for (i = 0; i <= n; ++i) {
        tapStart = fmax(0, i - ranges[i]);
        tapEnd = fmin(n, i + ranges[i]);
        for (j = tapStart; j <= tapEnd; ++j) {
            dp[tapEnd] = fmin(dp[tapEnd], dp[j] + 1);
        }
    }

    if (dp[n] != infinity) {
        retVal = dp[n];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int n;
        int ranges[MAX_SIZE];
        int rangesSize;
    } testCase[] = {{5, {3, 4, 1, 1, 0, 0}, 4}, {3, {0, 0, 0, 0}, 8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, ranges = [3,4,1,1,0,0]
     *  Output: 1
     *
     *  Input: n = 3, ranges = [0,0,0,0]
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, ranges = [", testCase[i].n);
        for (j = 0; j < testCase[i].rangesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].ranges[j]);
        }
        printf("]\n");

        answer = minTaps(testCase[i].n, testCase[i].ranges, testCase[i].rangesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
