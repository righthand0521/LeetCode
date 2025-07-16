#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximumLength(int* nums, int numsSize, int k) {
    int retVal = 0;

    int dp[k][k];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i] % k;
        for (int prev = 0; prev < k; prev++) {
            dp[prev][num] = dp[num][prev] + 1;
            if (dp[prev][num] > retVal) {
                retVal = dp[prev][num];
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e3)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5, 2}, {{1, 4, 2, 3, 1, 4}, 6, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,4,5], k = 2
     *  Output: 5
     *
     *  Input: nums = [1,4,2,3,1,4], k = 3
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maximumLength(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
