#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mincostTickets(int* days, int daysSize, int* costs, int costsSize) {
    int retVal = 0;

    int dpSize = days[daysSize - 1] + 1;
    int dp[dpSize];
    memset(dp, 0, sizeof(dp));

    int idx = 0;
    int i;
    for (i = 1; i < dpSize; ++i) {
        if (i != days[idx]) {
            dp[i] = dp[i - 1];
            continue;
        }
        dp[i] = fmin(dp[(int)(fmax(0, i - 1))] + costs[0], dp[(int)(fmax(0, i - 7))] + costs[1]);
        dp[i] = fmin(dp[i], dp[(int)(fmax(0, i - 30))] + costs[2]);
        ++idx;
    }
    retVal = dp[dpSize - 1];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (365)
    struct testCaseType {
        int days[MAX_SIZE];
        int daysSize;
        int costs[3];
        int costsSize;
    } testCase[] = {{{1, 4, 6, 7, 8, 20}, 6, {2, 7, 15}, 3},
                    {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31}, 12, {2, 7, 15}, 3},
                    {{1, 4, 6, 7, 8, 20}, 6, {7, 2, 15}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: days = [1,4,6,7,8,20], costs = [2,7,15]
     *  Output: 11
     *
     *  Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
     *  Output: 17
     *
     *  Input: days = [1,4,6,7,8,20], costs = [7,2,15]
     *  Output: 6
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: days = [");
        for (j = 0; j < testCase[i].daysSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].days[j]);
        }
        printf("], costs = [");
        for (j = 0; j < testCase[i].costsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].costs[j]);
        }
        printf("]\n");

        answer = mincostTickets(testCase[i].days, testCase[i].daysSize, testCase[i].costs, testCase[i].costsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
