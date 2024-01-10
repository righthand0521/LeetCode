#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minOperations(int* nums, int numsSize) {
    int retVal = 0;

    int diff;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i - 1] >= nums[i]) {
            diff = nums[i - 1] - nums[i] + 1;
            nums[i] += diff;
            retVal += diff;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 1, 1}, 3}, {{1, 5, 2, 4, 1}, 5}, {{8}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,1]
     *  Output: 3
     *
     *  Input: nums = [1,5,2,4,1]
     *  Output: 14
     *
     *  Input: nums = [8]
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", ((j == 0) ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minOperations(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
