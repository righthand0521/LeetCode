#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestArithSeqLength(int* nums, int numsSize) {
    int retVal = 1;

    int i;

    // 0 <= nums[i] <= 500
    int minNum = INT_MAX;
    int maxNum = INT_MIN;
    for (i = 0; i < numsSize; ++i) {
        minNum = fmin(minNum, nums[i]);
        maxNum = fmax(maxNum, nums[i]);
    }
    int diff = maxNum - minNum;

    int idx;
    int dp[maxNum + 1];
    int interval;
    for (interval = (-diff); interval <= diff; ++interval) {
        memset(dp, -1, sizeof(dp));

        for (i = 0; i < numsSize; ++i) {
            idx = nums[i] - interval;

            if ((idx >= minNum) && (idx <= maxNum) && (dp[idx] != -1)) {
                dp[nums[i]] = fmax(dp[nums[i]], dp[idx] + 1);
                retVal = fmax(retVal, dp[nums[i]]);
            }
            dp[nums[i]] = fmax(dp[nums[i]], 1);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 6, 9, 12}, 4}, {{9, 4, 7, 2, 10}, 5}, {{20, 1, 15, 3, 10, 5, 8}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,6,9,12]
     *  Output: 4
     *
     *  Input: nums = [9,4,7,2,10]
     *  Output: 3
     *
     *  Input: nums = [20,1,15,3,10,5,8]
     *  Output: 4
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = longestArithSeqLength(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
