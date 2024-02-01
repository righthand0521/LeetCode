#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** divideArray(int* nums, int numsSize, int k, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    if (numsSize % 3 != 0) {
        return pRetVal;
    }
    (*returnSize) = numsSize / 3;

    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit1;
    }
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        goto exit2;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int i, j;
    for (i = 0; i < (*returnSize); ++i) {
        if (nums[3 * i + 2] - nums[3 * i] > k) {
            goto exit3;
        }

        pRetVal[i] = (int*)malloc(3 * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            goto exit3;
        }
        memset(pRetVal[i], 0, (3 * sizeof(int)));
        (*returnColumnSizes)[i] = 3;
        pRetVal[i][0] = nums[3 * i];
        pRetVal[i][1] = nums[3 * i + 1];
        pRetVal[i][2] = nums[3 * i + 2];
    }

    return pRetVal;

exit3:
    for (j = 0; j < i; ++j) {
        free(pRetVal[j]);
        pRetVal[j] = NULL;
    }
    free((*returnColumnSizes));
    (*returnColumnSizes) = NULL;

exit2:
    free(pRetVal);
    pRetVal = NULL;

exit1:
    (*returnSize) = 0;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{1, 3, 4, 8, 7, 9, 3, 5, 1}, 9, 2, 0, NULL},
                    {{1, 3, 3, 2, 7, 3}, 6, 3, 0, NULL},
                    {{15, 13, 12, 13, 12, 14, 12, 2, 3, 13, 12, 14, 14, 13, 5, 12, 12, 2, 13, 2, 2}, 21, 2, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,4,8,7,9,3,5,1], k = 2
     *  Output: [[1,1,3],[3,4,5],[7,8,9]]
     *
     *  Input: nums = [1,3,3,2,7,3], k = 3
     *  Output: []
     *
     *  Input: nums = [15,13,12,13,12,14,12,2,3,13,12,14,14,13,5,12,12,2,13,2,2], k = 2
     *  Output: []
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pAnswer = divideArray(testCase[i].nums, testCase[i].numsSize, testCase[i].k, &testCase[i].returnSize,
                              &testCase[i].returnColumnSizes);
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

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
    }

    return EXIT_SUCCESS;
}
