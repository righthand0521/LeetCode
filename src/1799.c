#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int num1, int num2) {
    while (num2 != 0) {
        int temp = num1;
        num1 = num2;
        num2 = temp % num2;
    }
    return num1;
}
int maxScore(int *nums, int numsSize) {
    int retVal = 0;

    int maxStates = 1 << numsSize;
    int finalMask = maxStates - 1;
    int dp[maxStates];
    memset(dp, 0, sizeof(dp));

    int currentScore, stateAfterPickingCurrPair, remainingScore;
    int firstIndex;
    int numbersTaken, pairsFormed;
    int state;
    for (state = finalMask; state >= 0; state -= 1) {
        if (state == finalMask) {
            dp[state] = 0;
            continue;
        }

        numbersTaken = __builtin_popcount(state);
        pairsFormed = numbersTaken / 2;
        if (numbersTaken % 2) {
            continue;
        }

        for (firstIndex = 0; firstIndex < numsSize; firstIndex += 1) {
            for (int secondIndex = firstIndex + 1; secondIndex < numsSize; secondIndex += 1) {
                if (((state >> firstIndex) & 1) == 1 || ((state >> secondIndex) & 1) == 1) {
                    continue;
                }

                currentScore = (pairsFormed + 1) * gcd(nums[firstIndex], nums[secondIndex]);
                stateAfterPickingCurrPair = state | (1 << firstIndex) | (1 << secondIndex);
                remainingScore = dp[stateAfterPickingCurrPair];
                dp[state] = fmax(dp[state], currentScore + remainingScore);
            }
        }
    }
    retVal = dp[0];

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (16)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2}, 2}, {{3, 4, 6, 8}, 4}, {{1, 2, 3, 4, 5, 6}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2]
     *  Output: 1
     *
     *  Input: nums = [3,4,6,8]
     *  Output: 11
     *
     *  Input: nums = [1,2,3,4,5,6]
     *  Output: 14
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxScore(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
