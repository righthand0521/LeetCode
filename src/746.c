#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minCostClimbingStairs(int* cost, int costSize) {
    int retVal = 0;

    int dp0 = cost[0];
    int dp1 = cost[1];
    int i;
    for (i = 2; i < costSize; ++i) {
        retVal = cost[i] + fmin(dp0, dp1);
        dp0 = dp1;
        dp1 = retVal;
    }
    retVal = fmin(dp0, dp1);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int cost[MAX_SIZE];
        int costSize;
    } testCase[] = {{{10, 15, 20}, 3}, {{1, 100, 1, 1, 1, 100, 1, 1, 100, 1}, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: cost = [10,15,20]
     *  Output: 15
     *
     *  Input: cost = [1,100,1,1,1,100,1,1,100,1]
     *  Output: 6
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].costSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].cost[j]);
        }
        printf("]\n");

        answer = minCostClimbingStairs(testCase[i].cost, testCase[i].costSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
