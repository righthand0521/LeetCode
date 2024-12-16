#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getFinalState(int* nums, int numsSize, int k, int multiplier, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));
    memcpy(pRetVal, nums, (numsSize * sizeof(int)));
    (*returnSize) = numsSize;

    int minIndex;
    while (k--) {
        minIndex = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (pRetVal[i] < pRetVal[minIndex]) {
                minIndex = i;
            }
        }
        pRetVal[minIndex] *= multiplier;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
        int multiplier;
        int returnSize;
    } testCase[] = {{{2, 1, 3, 5, 6}, 5, 5, 2, 0}, {{1, 2}, 2, 3, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
     *  Output: [8,4,6,5,6]
     *
     *  Input: nums = [1,2], k = 3, multiplier = 4
     *  Output: [16,8]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d, multiplier = %d\n", testCase[i].k, testCase[i].multiplier);

        pAnswer = getFinalState(testCase[i].nums, testCase[i].numsSize, testCase[i].k, testCase[i].multiplier,
                                &testCase[i].returnSize);
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
