#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxAbsoluteSum(int* nums, int numsSize) {
    int retVal = 0;

    int prefixSum = 0;
    int minPrefixSum = 0;
    int maxPrefixSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        prefixSum += nums[i];
        minPrefixSum = fmin(minPrefixSum, prefixSum);
        maxPrefixSum = fmax(maxPrefixSum, prefixSum);
    }
    retVal = maxPrefixSum - minPrefixSum;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, -3, 2, 3, -4}, 5}, {{2, -5, 1, -4, 3, -2}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,-3,2,3,-4]
     *  Output: 5
     *
     *  Input: nums = [2,-5,1,-4,3,-2]
     *  Output: 8
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxAbsoluteSum(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
