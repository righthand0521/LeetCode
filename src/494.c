#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findTargetSumWays(int* nums, int numsSize, int target) {
    int retVal = 0;

    int totalSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        totalSum += nums[i];
    }

    int dpSize = 2 * totalSum + 1;
    int dp[dpSize];
    memset(dp, 0, sizeof(dp));
    dp[nums[0] + totalSum] = 1;    // Adding nums[0]
    dp[-nums[0] + totalSum] += 1;  // Subtracting nums[0]

    int next[dpSize];
    int index;
    for (index = 1; index < numsSize; index++) {
        memset(next, 0, sizeof(next));
        for (int sum = -totalSum; sum <= totalSum; sum++) {
            if (dp[sum + totalSum] <= 0) {
                continue;
            }
            next[sum + nums[index] + totalSum] += dp[sum + totalSum];
            next[sum - nums[index] + totalSum] += dp[sum + totalSum];
        }
        memcpy(dp, next, sizeof(dp));
    }

    // Return the result if the target is within the valid range
    if (abs(target) <= totalSum) {
        retVal = dp[target + totalSum];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int target;
    } testCase[] = {{{1, 1, 1, 1, 1}, 5, 3}, {{1}, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,1,1,1], target = 3
     *  Output: 5
     *
     *  Input: nums = [1], target = 1
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        answer = findTargetSumWays(testCase[i].nums, testCase[i].numsSize, testCase[i].target);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
