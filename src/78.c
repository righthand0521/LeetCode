#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    //
    int mallocSize = 1 << numsSize;
    pRetVal = (int**)malloc(mallocSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int*)malloc(mallocSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (mallocSize * sizeof(int)));

    //
    int i, j;
    for (i = 0; i < mallocSize; ++i) {
        pRetVal[i] = (int*)malloc(numsSize * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(pRetVal[i], 0, (numsSize * sizeof(int)));

        for (j = 0; j < numsSize; ++j) {
            if (i >> j & 1) {
                pRetVal[i][(*returnColumnSizes)[i]] = nums[j];
                (*returnColumnSizes)[i]++;
            }
        }
    }
    (*returnSize) = mallocSize;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{1, 2, 3}, 3, 0, NULL}, {{0}, 1, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3]
     *  Output: [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]]
     *
     *  Input: nums = [0]
     *  Output: [[], [0]]
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer =
            subsets(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
