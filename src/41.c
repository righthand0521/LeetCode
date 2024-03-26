#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int firstMissingPositive(int* nums, int numsSize) {
    int retVal = 0;

    int seenSize = numsSize + 1;
    int seen[seenSize];
    memset(seen, 0, sizeof(seen));

    int value;
    int i;
    for (i = 0; i < numsSize; ++i) {
        value = nums[i];
        if ((0 < value) && (value <= numsSize)) {
            seen[value] = 1;
        }
    }

    for (i = 1; i <= numsSize; ++i) {
        if (seen[i] == 0) {
            retVal = i;
            return retVal;
        }
    }
    retVal = numsSize + 1;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 0}, 3}, {{3, 4, -1, 1}, 4}, {{7, 8, 9, 11, 12}, 5}, {{2, 1}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,0]
     *  Output: 3
     *
     *  Input: nums = [3,4,-1,1]
     *  Output: 2
     *
     *  Input: nums = [7,8,9,11,12]
     *  Output: 1
     *
     *  Input: nums = [2, 1]
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = firstMissingPositive(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
