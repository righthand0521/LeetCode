#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long maximumProfit(int* prices, int pricesSize, int k) {
    long long retVal = 0;

    long long dp[k + 1][3];
    memset(dp, 0, sizeof(dp));
    for (int j = 1; j <= k; j++) {
        dp[j][1] = -prices[0];
        dp[j][2] = prices[0];
    }

    for (int i = 1; i < pricesSize; i++) {
        for (int j = k; j > 0; j--) {
            dp[j][0] = fmax(dp[j][0], fmax(dp[j][1] + prices[i], dp[j][2] - prices[i]));
            dp[j][1] = fmax(dp[j][1], dp[j - 1][0] - prices[i]);
            dp[j][2] = fmax(dp[j][2], dp[j - 1][0] + prices[i]);
        }
    }
    retVal = dp[k][0];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e3)
    struct testCaseType {
        int prices[MAX_SIZE];
        int pricesSize;
        int k;
    } testCase[] = {{{1, 7, 9, 8, 2}, 5, 2}, {{12, 16, 19, 19, 8, 1, 19, 13, 9}, 9, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: prices = [1,7,9,8,2], k = 2
     *  Output: 14
     *
     *  Input: prices = [12,16,19,19,8,1,19,13,9], k = 3
     *  Output: 36
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: prices = [");
        for (j = 0; j < testCase[i].pricesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].prices[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maximumProfit(testCase[i].prices, testCase[i].pricesSize, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
