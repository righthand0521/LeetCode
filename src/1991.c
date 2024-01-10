#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findMiddleIndex(int* nums, int numsSize) {
    int retVal = -1;

    int i;

    int sumLeft[numsSize];
    sumLeft[0] = nums[0];
    for (i = 1; i < numsSize; ++i) {
        sumLeft[i] = sumLeft[i - 1] + nums[i];
    }

    int sumRight[numsSize];
    sumRight[numsSize - 1] = nums[numsSize - 1];
    for (i = numsSize - 2; i >= 0; --i) {
        sumRight[i] = sumRight[i + 1] + nums[i];
    }

    for (i = 0; i < numsSize; ++i) {
        if (sumLeft[i] == sumRight[i]) {
            retVal = i;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 3, -1, 8, 4}, 6}, {{1, -1, 4}, 3}, {{2, 5}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,3,-1,8,4]
     *  Output: 3
     *
     *  Input: nums = [1,-1,4]
     *  Output: 2
     *
     *  Input: nums = [2,5]
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = findMiddleIndex(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
