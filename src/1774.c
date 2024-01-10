#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
int closestCost(int* baseCosts, int baseCostsSize, int* toppingCosts, int toppingCostsSize, int target) {
    int retVal = INT_MAX;

    int i, j;

    for (i = 0; i < baseCostsSize; ++i) {
        retVal = MIN(retVal, baseCosts[i]);
    }
    if (retVal >= target) {
        return retVal;
    }

    bool dp[target + 1];
    memset(dp, false, sizeof(dp));

    retVal = 2 * target - retVal;
    for (i = 0; i < baseCostsSize; ++i) {
        if (baseCosts[i] <= target) {
            dp[baseCosts[i]] = true;
        } else {
            retVal = MIN(retVal, baseCosts[i]);
        }
    }

    int toppingCount;
    for (j = 0; j < toppingCostsSize; ++j) {
        for (toppingCount = 0; toppingCount < 2; ++toppingCount) {
            for (i = target; i > 0; --i) {
                if (dp[i] && (i + toppingCosts[j] > target)) {
                    retVal = MIN(retVal, (i + toppingCosts[j]));
                }

                if (i - toppingCosts[j] > 0) {
                    dp[i] = dp[i] | (dp[i - toppingCosts[j]]);
                }
            }
        }
    }

    for (i = 0; i <= (retVal - target); ++i) {
        if (dp[target - i]) {
            retVal = target - i;
            return retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10)
    struct testCaseType {
        int baseCosts[MAX_SIZE];
        int baseCostsSize;
        int toppingCosts[MAX_SIZE];
        int toppingCostsSize;
        int target;
    } testCase[] = {{{1, 7}, 2, {3, 4}, 2, 10}, {{2, 3}, 2, {4, 5, 100}, 3, 18}, {{3, 10}, 2, {2, 5}, 2, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: baseCosts = [");
        for (j = 0; j < testCase[i].baseCostsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].baseCosts[j]);
        }
        printf("], toppingCosts = [");
        for (j = 0; j < testCase[i].toppingCostsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].toppingCosts[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        answer = closestCost(testCase[i].baseCosts, testCase[i].baseCostsSize, testCase[i].toppingCosts,
                             testCase[i].toppingCostsSize, testCase[i].target);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
