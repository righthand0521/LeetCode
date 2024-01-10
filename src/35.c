#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int searchInsert(int* nums, int numsSize, int target) {
    int retVal = 0;

    int middle;
    int left = 0;
    int right = numsSize - 1;
    while (left <= right) {
        middle = left + (right - left) / 2;
        if (nums[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int target;
    } testCase[] = {{{1, 3, 5, 6}, 4, 5}, {{1, 3, 5, 6}, 4, 2}, {{1, 3, 5, 6}, 4, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,5,6], target = 5
     *  Output: 2
     *
     *  Input: nums = [1,3,5,6], target = 2
     *  Output: 1
     *
     *  Input: nums = [1,3,5,6], target = 7
     *  Output: 4
     */

    int pAnswer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        pAnswer = searchInsert(testCase[i].nums, testCase[i].numsSize, testCase[i].target);
        printf("Output: %d\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
