#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxSubArray(int* nums, int numsSize) {
    int retVal = INT_MIN;

    // Kadane’s Algorithm: https://en.wikipedia.org/wiki/Maximum_subarray_problem
    int sum = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        sum = fmax(nums[i], (sum + nums[i]));
        retVal = fmax(retVal, sum);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{-2, 1, -3, 4, -1, 2, 1, -5, 4}, 9}, {{1}, 1}, {{5, 4, -1, 7, 8}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
     *  Output: 6
     *
     *  Input: nums = [1]
     *  Output: 1
     *
     *  Input: nums = [5,4,-1,7,8]
     *  Output: 23
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxSubArray(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
