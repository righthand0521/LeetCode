#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canPartitionKSubsets(int* nums, int numsSize, int k) {
    bool retVal = false;

    int i;

    int sumOfNums = 0;
    for (i = 0; i < numsSize; ++i) {
        sumOfNums += nums[i];
    }
    if (sumOfNums % k != 0) {
        return retVal;
    }
    int average = sumOfNums / k;

    int dpSize = (1 << numsSize);
    int dp[dpSize];
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    int key, value;
    int j;
    for (i = 1; i < dpSize; ++i) {
        for (key = 0; key < numsSize; ++key) {
            value = nums[key];
            if ((i & (1 << key)) == 0) {
                continue;
            }
            j = i & ~(1 << key);

            if ((dp[j] >= 0) && (dp[j] + value <= average)) {
                dp[i] = (dp[j] + value) % average;
                break;
            }
        }
    }
    retVal = (dp[dpSize - 1] == 0);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (16)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{4, 3, 2, 3, 5, 2, 1}, 7, 4}, {{1, 2, 3, 4}, 4, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,3,2,3,5,2,1], k = 4
     *  Output: true
     *
     *  Input: nums = [1,2,3,4], k = 3
     *  Output: false
     */

    int i, j;
    bool answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = canPartitionKSubsets(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
