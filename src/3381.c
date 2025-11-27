#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long maxSubarraySum(int* nums, int numsSize, int k) {
    long long retVal = 0;

    long long prefixSum = 0;
    long long maxSum = LONG_MIN;
    long long kSum[k];
    for (int i = 0; i < k; i++) {
        kSum[i] = LLONG_MAX / 2;
    }
    kSum[k - 1] = 0;

    for (int i = 0; i < numsSize; i++) {
        prefixSum += nums[i];
        if (prefixSum - kSum[i % k] > maxSum) {
            maxSum = prefixSum - kSum[i % k];
        }
        if (prefixSum < kSum[i % k]) {
            kSum[i % k] = prefixSum;
        }
    }
    retVal = maxSum;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(2 * 100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 2}, 2, 1}, {{-1, -2, -3, -4, -5}, 5, 4}, {{-5, 1, 2, -3, 4}, 5, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2], k = 1
     *  Output: 3
     *
     *  Input: nums = [-1,-2,-3,-4,-5], k = 4
     *  Output: -10
     *
     *  Input: nums = [-5,1,2,-3,4], k = 2
     *  Output: 4
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maxSubarraySum(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
