#include <limits.h>
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
int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    pRetVal = (int**)malloc(arrSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    qsort(arr, arrSize, sizeof(int), compareInteger);
    int minDiff = INT_MAX;
    for (int i = 1; i < arrSize; ++i) {
        int diff = arr[i] - arr[i - 1];
        if (diff < minDiff) {
            minDiff = diff;
            for (int j = 0; j < (*returnSize); ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            (*returnSize) = 0;
            pRetVal[(*returnSize)] = (int*)malloc(2 * sizeof(int));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                goto exit;
            }
            pRetVal[(*returnSize)][0] = arr[i - 1];
            pRetVal[(*returnSize)][1] = arr[i];
            (*returnSize)++;
        } else if (diff == minDiff) {
            pRetVal[(*returnSize)] = (int*)malloc(2 * sizeof(int));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                goto exit;
            }
            pRetVal[(*returnSize)][0] = arr[i - 1];
            pRetVal[(*returnSize)][1] = arr[i];
            (*returnSize)++;
        }
    }

    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        goto exit;
    }
    for (int i = 0; i < (*returnSize); ++i) {
        (*returnColumnSizes)[i] = 2;
    }

    return pRetVal;

exit:
    for (int i = 0; i < (*returnSize); ++i) {
        free(pRetVal[i]);
        pRetVal[i] = NULL;
    }
    free(pRetVal);
    pRetVal = NULL;
    (*returnSize) = 0;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {
        {{4, 2, 1, 3}, 4, 0, NULL}, {{1, 3, 6, 10, 15}, 5, 0, NULL}, {{3, 8, -10, 23, 19, -4, -14, 27}, 8, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [4,2,1,3]
     *  Output: [[1,2],[2,3],[3,4]]
     *
     *  Input: arr = [1,3,6,10,15]
     *  Output: [[1,3]]
     *
     *  Input: arr = [3,8,-10,23,19,-4,-14,27]
     *  Output: [[-14,-10],[19,23],[23,27]]
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        pAnswer = minimumAbsDifference(testCase[i].arr, testCase[i].arrSize, &testCase[i].returnSize,
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
