#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int singleNumber(int* nums, int numsSize) {
    int retVal = 0;

    int ones = 0;
    int twos = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        ones = ((ones ^ nums[i]) & (~twos));
        twos = ((twos ^ nums[i]) & (~ones));
    }
    retVal = ones;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 2, 3, 2}, 4}, {{0, 1, 0, 1, 0, 1, 99}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,2,3,2]
     *  Output: 3
     *
     *  Input: nums = [0,1,0,1,0,1,99]
     *  Output: 99
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = singleNumber(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
