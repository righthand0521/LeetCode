#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int profitableSchemes(int n, int minProfit, int* group, int groupSize, int* profit, int profitSize) {
    int retVal = 0;

    int i, j, k;

    int dp[n + 1][minProfit + 1];
    memset(dp, 0, sizeof(dp));
    for (i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    int members;
    int earn;
    for (i = 1; i <= groupSize; i++) {
        members = group[i - 1];
        earn = profit[i - 1];
        for (j = n; j >= members; j--) {
            for (k = minProfit; k >= 0; k--) {
                dp[j][k] = (dp[j][k] + dp[j - members][(int)fmax(0, k - earn)]) % MODULO;
            }
        }
    }
    retVal = dp[n][minProfit];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int n;
        int minProfit;
        int group[MAX_SIZE];
        int groupSize;
        int profit[MAX_SIZE];
        int profitSize;
    } testCase[] = {{5, 3, {2, 2}, 2, {2, 3}, 2}, {10, 5, {2, 3, 5}, 3, {6, 7, 8}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, minProfit = 3, group = [2,2], profit = [2,3]
     *  Output: 2
     *
     *  Input: n = 10, minProfit = 5, group = [2,3,5], profit = [6,7,8]
     *  Output: 7
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, minProfit = %d, group = [", testCase[i].n, testCase[i].minProfit);
        for (j = 0; j < testCase[i].groupSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].group[j]);
        }
        printf("], profit = [");
        for (j = 0; j < testCase[i].groupSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].profit[j]);
        }
        printf("]\n");

        answer = profitableSchemes(testCase[i].n, testCase[i].minProfit, testCase[i].group, testCase[i].groupSize,
                                   testCase[i].profit, testCase[i].profitSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
