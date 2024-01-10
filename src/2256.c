#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumAverageDifference(int* nums, int numsSize) {
    int retVal = 0;

    // Boundary Conditions: numsSize is 1
    if (numsSize == 1) {
        return retVal;
    }

    // Prepare sum of all elements
    long long sum = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        sum += nums[i];
    }

    long long currentDiff;
    long long minDiff = LONG_MAX;
    long long prefixSum = 0;
    // avoid divide zero, so prefix range from 0 to (numsSize - 1).
    for (i = 0; i < (numsSize - 1); ++i) {
        prefixSum += nums[i];
        sum -= nums[i];
        currentDiff = abs((prefixSum / (i + 1)) - (sum / (numsSize - (i + 1))));
        if (minDiff > currentDiff) {
            minDiff = currentDiff;
            retVal = i;
        }
    }

    // Boundary Conditions: prefix has numsSize elements, others is zero.
    prefixSum += nums[i];
    currentDiff = (prefixSum / (i + 1));
    if (minDiff > currentDiff) {
        minDiff = currentDiff;
        retVal = i;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 5, 3, 9, 5, 3}, 6}, {{0}, 1}, {{4, 2, 0}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minimumAverageDifference(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
