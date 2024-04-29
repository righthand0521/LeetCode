#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minOperations(int* nums, int numsSize, int k) {
    int retVal = 0;

    int xorValue = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        xorValue ^= nums[i];
    }
    xorValue ^= k;
    retVal = __builtin_popcount(xorValue);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{2, 1, 3, 4}, 4, 1}, {{2, 0, 2, 0}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,1,3,4], k = 1
     *  Output: 2
     *
     *  Input: nums = [2,0,2,0], k = 0
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = minOperations(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
