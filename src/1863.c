#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int subsetXORSum(int* nums, int numsSize) {
    int retVal = 0;

    // Capture each bit that is set in any of the elements
    int i;
    for (i = 0; i < numsSize; ++i) {
        retVal |= nums[i];
    }

    // Multiply by the number of subset XOR totals that will have each bit set
    retVal = retVal << (numsSize - 1);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (12)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3}, 2}, {{5, 1, 6}, 3}, {{3, 4, 5, 6, 7, 8}, 6}, {{2, 4, 4}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3]
     *  Output: 6
     *
     *  Input: nums = [5,1,6]
     *  Output: 28
     *
     *  Input: nums = [3,4,5,6,7,8]
     *  Output: 480
     *
     *  Input: nums = [2,4,4]
     *  Output: 24
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = subsetXORSum(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
