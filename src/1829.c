#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getMaximumXor(int *nums, int numsSize, int maximumBit, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));

    int xorProduct = 0;
    for (int i = 0; i < numsSize; i++) {
        xorProduct = xorProduct ^ nums[i];
    }

    int mask = (1 << maximumBit) - 1;
    for (int i = 0; i < numsSize; i++) {
        pRetVal[(*returnSize)++] = (xorProduct ^ mask);
        // remove last element
        xorProduct = xorProduct ^ nums[numsSize - 1 - i];
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int maximumBit;
        int returnSize;
    } testCase[] = {{{0, 1, 1, 3}, 4, 2, 0}, {{2, 3, 4, 7}, 4, 3, 0}, {{0, 1, 2, 2, 5, 7}, 6, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,1,1,3], maximumBit = 2
     *  Output: [0,3,2,3]
     *
     *  Input: nums = [2,3,4,7], maximumBit = 3
     *  Output: [5,2,6,5]
     *
     *  Input: nums = [0,1,2,2,5,7], maximumBit = 3
     *  Output: [4,3,6,4,6,7]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], maximumBit = %d\n", testCase[i].maximumBit);

        pAnswer =
            getMaximumXor(testCase[i].nums, testCase[i].numsSize, testCase[i].maximumBit, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
