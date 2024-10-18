#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countMaxOrSubsets(int* nums, int numsSize) {
    int retVal = 0;

    int dp[1 << 17];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    int max = 0;
    int i, j;
    for (i = 0; i < numsSize; ++i) {
        for (j = max; j >= 0; --j) {
            dp[j | nums[i]] += dp[j];
        }
        max |= nums[i];
    }
    retVal = dp[max];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (16)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 1}, 2}, {{2, 2, 2}, 3}, {{3, 2, 1, 5}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,1]
     *  Output: 2
     *
     *  Input: nums = [2,2,2]
     *  Output: 7
     *
     *  Input: nums = [3,2,1,5]
     *  Output: 6
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = countMaxOrSubsets(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
