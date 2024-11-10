#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void updateBitCounts(int* bitCounts, int bitCountsSize, int number, int delta) {
    int bitPosition;
    for (bitPosition = 0; bitPosition < bitCountsSize; bitPosition++) {
        if ((number >> bitPosition) & 1) {
            bitCounts[bitPosition] += delta;
        }
    }
}
int convertBitCountsToNumber(int* bitCounts, int bitCountsSize) {
    int retVal = 0;

    int bitPosition = 0;
    for (bitPosition = 0; bitPosition < bitCountsSize; bitPosition++) {
        if (bitCounts[bitPosition] != 0) {
            retVal |= (1 << bitPosition);
        }
    }

    return retVal;
}
int minimumSubarrayLength(int* nums, int numsSize, int k) {
    int retVal = -1;

    int bitCountsSize = 32;
    int* bitCounts = (int*)calloc(bitCountsSize, sizeof(int));
    if (bitCounts == NULL) {
        perror("calloc");
        return retVal;
    }
    int minLength = INT_MAX;
    int windowStart = 0;
    int windowEnd;
    for (windowEnd = 0; windowEnd < numsSize; ++windowEnd) {
        updateBitCounts(bitCounts, bitCountsSize, nums[windowEnd], 1);

        while ((windowStart <= windowEnd) && (convertBitCountsToNumber(bitCounts, bitCountsSize) >= k)) {
            minLength = fmin(minLength, windowEnd - windowStart + 1);
            updateBitCounts(bitCounts, bitCountsSize, nums[windowStart], -1);
            windowStart++;
        }
    }

    if (minLength != INT_MAX) {
        retVal = minLength;
    }

    //
    free(bitCounts);
    bitCounts = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 2, 3}, 3, 2}, {{2, 1, 8}, 3, 10}, {{1, 2}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3], k = 2
     *  Output: 1
     *
     *  Input: nums = [2,1,8], k = 10
     *  Output: 3
     *
     *  Input: nums = [1,2], k = 0
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = minimumSubarrayLength(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
