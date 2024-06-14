#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minIncrementForUnique(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int increment;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] <= nums[i - 1]) {
            increment = nums[i - 1] + 1 - nums[i];
            retVal += increment;
            nums[i] = nums[i - 1] + 1;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 2}, 3}, {{3, 2, 1, 2, 1, 7}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,2]
     *  Output: 1
     *
     *  Input: nums = [3,2,1,2,1,7]
     *  Output: 6
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minIncrementForUnique(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
