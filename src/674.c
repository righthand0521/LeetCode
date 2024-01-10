#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findLengthOfLCIS(int* nums, int numsSize) {
    int retVal = 0;

    int previousNum = INT_MIN;  // - 10 ^ 9 <= nums[i] <= 10 ^ 9
    int count = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] > previousNum) {
            ++count;
        } else {
            retVal = fmax(retVal, count);
            count = 1;
        }
        previousNum = nums[i];
    }
    retVal = fmax(retVal, count);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3, 5, 4, 7}, 5}, {{2, 2, 2, 2, 2}, 5}, {{1, 3, 5, 7}, 4}, {{1, 3, 5, 4, 2, 3, 4, 5}, 8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,5,4,7]
     *  Output: 3
     *
     *  Input: nums = [2,2,2,2,2]
     *  Output: 1
     *
     *  Input: nums = [1,3,5,7]
     *  Output: 4
     *
     *  Input: nums = [1,3,5,4,2,3,4,5]
     *  Output: 4
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = findLengthOfLCIS(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
