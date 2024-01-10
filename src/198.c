#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rob(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize == 0) {
        return retVal;
    } else if (numsSize == 1) {
        retVal = nums[0];
        return retVal;
    }

    int first = nums[0];
    int second = fmax(nums[0], nums[1]);
    int temp;
    int i;
    for (i = 2; i < numsSize; ++i) {
        temp = second;
        second = fmax(first + nums[i], second);
        first = temp;
    }
    retVal = second;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 1}, 4}, {{2, 7, 9, 3, 1}, 5}, {{2, 1}, 2}, {{2, 1, 1, 2}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,1]
     *  Output: 4
     *
     *  Input: nums = [2,7,9,3,1]
     *  Output: 12
     *
     *  Input: nums = [2, 1]
     *  Output: 2
     *
     *  Input: nums = [2, 1, 1, 2]
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = rob(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
