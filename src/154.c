#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findMin(int* nums, int numsSize) {
    int retVal = 0;

    int middle = 0;
    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (nums[middle] < nums[right]) {
            right = middle;
        } else if (nums[middle] > nums[right]) {
            left = middle + 1;
        } else {
            right -= 1;
        }
    }
    retVal = nums[left];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3, 5}, 3}, {{2, 2, 2, 0, 1}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example 1:
     *  Input: nums = [1,3,5]
     *  Output: 1
     *
     *  Input: nums = [2,2,2,0,1]
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

        answer = findMin(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
