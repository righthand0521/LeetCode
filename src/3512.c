#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minOperations(int* nums, int numsSize, int k) {
    int retVal = 0;

    for (int i = 0; i < numsSize; ++i) {
        retVal += nums[i];
    }
    retVal %= k;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{3, 9, 7}, 3, 5}, {{4, 1, 3}, 3, 4}, {{3, 2}, 2, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,9,7], k = 5
     *  Output: 4
     *
     *  Input: nums = [4,1,3], k = 4
     *  Output: 0
     *
     *  Input: nums = [3,2], k = 6
     *  Output: 5
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
