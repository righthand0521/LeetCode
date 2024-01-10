#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxSubarraySumCircular(int* nums, int numsSize) {
    int retVal = 0;

    /* Kadane’s Algorithm: https://en.wikipedia.org/wiki/Maximum_subarray_problem
     *  1. Maximum Subarray is not Circular: maxSum
     *  2. Maximum Subarray is Circular: sum - minSum
     */
    int curMax = 0;
    int maxSum = nums[0];
    int curMin = 0;
    int minSum = nums[0];
    int sum = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        curMax = fmax(curMax, 0) + nums[i];
        maxSum = fmax(maxSum, curMax);

        curMin = fmin(curMin, 0) + nums[i];
        minSum = fmin(minSum, curMin);

        sum += nums[i];
    }

    if (sum == minSum) {
        retVal = maxSum;
    } else {
        retVal = fmax(maxSum, (sum - minSum));
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, -2, 3, -2}, 4}, {{5, -3, 5}, 3}, {{-3, -2, -3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxSubarraySumCircular(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
