#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findPeakElement(int* nums, int numsSize) {
    int retVal = 0;

    int left = 0;
    int right = numsSize - 1;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (nums[middle] > nums[middle + 1]) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 1}, 4}, {{1, 2, 1, 3, 5, 6, 4}, 7}, {{1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,1]
     *  Output: 2
     *
     *  Input: nums = [1,2,1,3,5,6,4]
     *  utput: 5
     *
     *  Input: nums = [1]
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = findPeakElement(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
