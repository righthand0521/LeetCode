#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define METHOD_SUM (0)
#define METHOD_XOR (1)
int missingNumber(int* nums, int numsSize) {
#if (METHOD_SUM)
    int retVal = (numsSize * (numsSize + 1)) / 2;
#elif (METHOD_XOR)
    int retVal = numsSize;
#endif

    int i;
    for (i = 0; i < numsSize; ++i) {
#if (METHOD_SUM)
        retVal -= nums[i];
#elif (METHOD_XOR)
        retVal ^= i;
        retVal ^= nums[i];
#endif
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 0, 1}, 3}, {{0, 1}, 2}, {{9, 6, 4, 2, 3, 5, 7, 0, 1}, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,0,1]
     *  Output: 2
     *
     *  Input: nums = [0,1]
     *  Output: 2
     *
     *  Input: nums = [9,6,4,2,3,5,7,0,1]
     *  Output: 8
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = missingNumber(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
