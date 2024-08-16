#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canPartition(int* nums, int numsSize) {
    bool retVal = false;

    int i, j;

    int sum = 0;
    for (i = 0; i < numsSize; ++i) {
        sum += nums[i];
    }
    if (sum % 2 != 0) {
        return retVal;
    }
    sum /= 2;

    bool dp[sum + 1];
    memset(dp, false, sizeof(dp));
    dp[0] = true;
    for (i = 0; i < numsSize; ++i) {
        for (j = sum; j >= nums[i]; --j) {
            dp[j] = dp[j] | dp[j - nums[i]];
        }
    }
    retVal = dp[sum];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 5, 11, 5}, 4}, {{1, 2, 3, 5}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,5,11,5]
     *  Output: true
     *
     *  Input: nums = [1,2,3,5]
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = canPartition(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
