#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findMin(int *nums, int numsSize) {
    int retVal = 0;

    int middle = 0;
    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (nums[middle] < nums[right]) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = nums[left];

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {
        {{3, 4, 5, 1, 2}, 5}, {{4, 5, 6, 7, 0, 1, 2}, 7}, {{11, 13, 15, 17}, 4}, {{2, 1}, 2}, {{2, 3, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,4,5,1,2]
     *  Output: 1
     *
     *  Input: nums = [4,5,6,7,0,1,2]
     *  Output: 0
     *
     *  Input: nums = [11,13,15,17]
     *  Output: 11
     *
     *  Input: nums = [2,1]
     *  Output: 1
     *
     *  Input: nums = [2,3,1]
     *  Output: 1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = findMin(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
