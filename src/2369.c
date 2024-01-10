#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validPartition(int* nums, int numsSize) {
    bool retVal = false;

    bool dp[numsSize + 1];
    memset(dp, false, sizeof(dp));
    dp[0] = true;
    // dp[i] represents if the prefix of length i can form a valid partition
    //  dp[index] : dp[index - 2] && (nums[i - 1] == nums[i])
    //  dp[index] : dp[index - 3] && (nums[i - 2] == nums[i - 1] == nums[i])
    //  dp[index] : dp[index - 3] && (nums[i - 2] + 2 == nums[i - 1] + 1 == nums[i])
    int index;
    int i;
    for (i = 0; i < numsSize; ++i) {
        index = i + 1;
        if ((i > 0) && (nums[i - 1] == nums[i])) {
            dp[index] = dp[index] | dp[index - 2];
        }
        if ((i > 1) && (nums[i - 2] == nums[i]) && (nums[i - 1] == nums[i])) {
            dp[index] = dp[index] | dp[index - 3];
        }
        if ((i > 1) && (nums[i - 2] + 2 == nums[i]) && (nums[i - 1] + 1 == nums[i])) {
            dp[index] = dp[index] | dp[index - 3];
        }
    }
    retVal = dp[numsSize];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{4, 4, 4, 5, 6}, 5}, {{1, 1, 1, 2}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,4,4,5,6]
     *  Output: true
     *
     *  Input: nums = [1,1,1,2]
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = validPartition(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
