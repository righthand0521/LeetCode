#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int combinationSum4(int* nums, int numsSize, int target) {
    int retVal = 0;

    unsigned long dp[target + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    int i, j;
    for (i = 1; i <= target; ++i) {
        for (j = 0; j < numsSize; ++j) {
            if (i >= nums[j]) {
                dp[i] += dp[i - nums[j]];
            }
        }
    }
    retVal = dp[target];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int target;
    } testCase[] = {{{1, 2, 3}, 3, 4}, {{9}, 1, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3], target = 4
     *  Output: 7
     *
     *  Input: nums = [9], target = 3
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        answer = combinationSum4(testCase[i].nums, testCase[i].numsSize, testCase[i].target);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
