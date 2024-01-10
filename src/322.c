#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int coinChange(int* coins, int coinsSize, int amount) {
    int retVal = -1;

    int dp[amount + 1];
    memset(dp, 0, sizeof(dp));

    int i, j;
    for (i = 1; i <= amount; ++i) {
        dp[i] = amount + 1;

        for (j = 0; j < coinsSize; ++j) {
            if (coins[j] <= i) {
                dp[i] = fmin(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }
    if (dp[amount] <= amount) {
        retVal = dp[amount];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (12)
    struct testCaseType {
        int coins[MAX_SIZE];
        int coinsSize;
        int amount;
    } testCase[] = {{{1, 2, 5}, 3, 11}, {{2}, 1, 3}, {{1}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: coins = [1,2,5], amount = 11
     *  Output: 3
     *
     *  Input: coins = [2], amount = 3
     *  Output: -1
     *
     *  Input: coins = [1], amount = 0
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: coins = [");
        for (j = 0; j < testCase[i].coinsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].coins[j]);
        }
        printf("], amount = %d\n", testCase[i].amount);

        answer = coinChange(testCase[i].coins, testCase[i].coinsSize, testCase[i].amount);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
