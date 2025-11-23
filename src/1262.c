#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxSumDivThree(int* nums, int numsSize) {
    int retVal = 0;

    int dp[3] = {0, INT_MIN, INT_MIN};
    int tmp[3] = {0};
    for (int j = 0; j < numsSize; j++) {
        memcpy(tmp, dp, sizeof(dp));
        for (int i = 0; i < 3; i++) {
            tmp[(i + nums[j] % 3) % 3] = fmax(tmp[(i + nums[j] % 3) % 3], dp[i] + nums[j]);
        }
        memcpy(dp, tmp, sizeof(dp));
    }
    retVal = dp[0];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(4 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 6, 5, 1, 8}, 5}, {{4}, 1}, {{1, 2, 3, 4, 4}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,6,5,1,8]
     *  Output: 18
     *
     *  Input: nums = [4]
     *  Output: 0
     *
     *  Input: nums = [1,2,3,4,4]
     *  Output: 12
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxSumDivThree(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
