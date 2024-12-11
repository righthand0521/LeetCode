#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximumBeauty(int* nums, int numsSize, int k) {
    int retVal = 0;

    if (numsSize == 1) {  // If there's only one element, the maximum beauty is 1
        retVal = 1;
        return retVal;
    }

    int maxValue = 0;
    for (int i = 0; i < numsSize; ++i) {
        maxValue = fmax(maxValue, nums[i]);
    }

    int countSize = maxValue + 1;
    int count[maxValue + 1];
    memset(count, 0, sizeof(count));
    int idx;
    for (int i = 0; i < numsSize; ++i) {
        idx = fmax(nums[i] - k, 0);
        count[idx]++;  // Increment at the start of the range
        if (nums[i] + k + 1 <= maxValue) {
            count[nums[i] + k + 1]--;  // Decrement after the range
        }
    }

    // Calculate the prefix sum and find the maximum value
    int currentSum = 0;
    for (int i = 0; i < countSize; ++i) {
        currentSum += count[i];
        retVal = fmax(retVal, currentSum);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{4, 6, 1, 2}, 4, 2}, {{1, 1, 1, 1}, 4, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,6,1,2], k = 2
     *  Output: 3
     *
     *  Input: nums = [1,1,1,1], k = 10
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

        answer = maximumBeauty(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
