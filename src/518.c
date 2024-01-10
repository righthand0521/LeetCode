#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int change(int amount, int* coins, int coinsSize) {
    int retVal = 0;

    int dp[amount + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    int i, j;
    for (i = 0; i < coinsSize; ++i) {
        for (j = coins[i]; j <= amount; ++j) {
            dp[j] += dp[j - coins[i]];
        }
    }
    retVal = dp[amount];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        int amount;
        int coins[MAX_SIZE];
        int coinsSize;
    } testCase[] = {{5, {1, 2, 5}, 3}, {3, {2}, 1}, {10, {10}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: amount = 5, coins = [1,2,5]
     *  Output: 4
     *
     *  Input: amount = 3, coins = [2]
     *  Output: 0
     *
     *  Input: amount = 10, coins = [10]
     *  Output: 1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: amount = %d, coins = [", testCase[i].amount);
        for (j = 0; j < testCase[i].coinsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].coins[j]);
        }
        printf("]\n");

        answer = change(testCase[i].amount, testCase[i].coins, testCase[i].coinsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
