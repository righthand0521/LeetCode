#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int singleNonDuplicate(int* nums, int numsSize) {
    int retVal = 0;

    // 1 <= nums.length <= 10^5
    if (numsSize == 1) {
        retVal = nums[0];
        return retVal;
    }

    int middle = 0;
    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        middle = left + (right - left) / 2;
        /* middle is odd or even
         *  middle is odd: middle % 2 == 1
         *  +---------------------------------+
         *  |  0  | 1 | 2 | [3] | 4 | 5 |  6  |
         *  +---------------------------------+
         *  |  1  | 1 | 2 |  2  | 3 | 3 | (4) | nums[middle] == nums[middle - 1]
         *  | (1) | 2 | 2 |  3  | 3 | 4 |  4  | nums[middle] != nums[middle - 1]
         *  +---------------------------------+
         *
         *  middle is even: middle % 2 == 0
         *  +-----------------------------------------+
         *  |  0  | 1 | 2 | 3 | [4] | 5 | 6 | 7 |  8  |
         *  +-----------------------------------------+
         *  | (1) | 2 | 2 | 3 |  3  | 4 | 4 | 5 |  5  | nums[middle] == nums[middle - 1]
         *  |  1  | 1 | 2 | 2 |  3  | 3 | 4 | 4 | (5) | nums[middle] != nums[middle - 1]
         *  +-----------------------------------------+
         */
        if (middle % 2 == 1) {
            if (nums[middle] == nums[middle - 1]) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        } else {
            if (nums[middle] == nums[middle - 1]) {
                right = middle;
            } else {
                left = middle;
            }
        }
    }
    retVal = nums[left];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 1, 2, 3, 3, 4, 4, 8, 8}, 9}, {{3, 3, 7, 7, 10, 11, 11}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,2,3,3,4,4,8,8]
     *  Output: 2
     *
     *  Input: nums = [3,3,7,7,10,11,11]
     *  Output: 10
     */

    int pAnswer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = singleNonDuplicate(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
