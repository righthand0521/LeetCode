#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int removeDuplicates(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize < 2) {
        retVal = numsSize;
        return retVal;
    }

    int count = 0;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[retVal] != nums[i]) {
            count = 0;
        } else {
            count++;
        }

        if (count < 2) {
            retVal++;
            nums[retVal] = nums[i];
        }
    }
    retVal += 1;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 1, 1, 2, 2, 3}, 6}, {{0, 0, 1, 1, 1, 1, 2, 3, 3}, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,1,2,2,3]
     *  Output: 5, nums = [1,1,2,2,3,_]
     *
     *  Input: nums = [0,0,1,1,1,1,2,3,3]
     *  Output: 7, nums = [0,0,1,1,2,3,3,_,_]
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", ((j == 0) ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = removeDuplicates(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d, nums = [", answer);
        for (j = 0; j < answer; ++j) {
            printf("%s%d", ((j == 0) ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
