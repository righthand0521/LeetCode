#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int paintWalls(int* cost, int costSize, int* time, int timeSize) {
    int retVal = 0;

    const int INF = 1e9;  // 1 <= cost.length <= 500, 1 <= cost[i] <= 10^6.
    int i, j;

    int dp[costSize + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 0;
    for (i = 1; i <= costSize; i++) {
        dp[i] = INF;
    }

    int idx;
    for (i = 0; i < costSize; i++) {
        for (j = costSize; j >= 0; j--) {
            idx = fmax(j - time[i] - 1, 0);
            dp[j] = fmin(dp[j], dp[idx] + cost[i]);
        }
    }
    retVal = dp[costSize];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int cost[MAX_SIZE];
        int costSize;
        int time[MAX_SIZE];
        int timeSize;
    } testCase[] = {{{1, 2, 3, 2}, 4, {1, 2, 3, 2}, 4}, {{2, 3, 4, 2}, 4, {1, 1, 1, 1}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: cost = [1,2,3,2], time = [1,2,3,2]
     *  Output: 3
     *
     *  Input: cost = [2,3,4,2], time = [1,1,1,1]
     *  Output: 4
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: cost = [");
        for (j = 0; j < testCase[i].costSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].cost[j]);
        }
        printf("], time = [");
        for (j = 0; j < testCase[i].timeSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].time[j]);
        }
        printf("]\n");

        answer = paintWalls(testCase[i].cost, testCase[i].costSize, testCase[i].time, testCase[i].timeSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
