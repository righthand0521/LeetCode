#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _rCenter;
int _cCenter;
int compareIntArray(const void* a, const void* b) {
    int* p1 = *(int**)a;
    int* p2 = *(int**)b;

    // ascending order
    return fabs(p1[0] - _rCenter) + fabs(p1[1] - _cCenter) - fabs(p2[0] - _rCenter) - fabs(p2[1] - _cCenter);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** allCellsDistOrder(int rows, int cols, int rCenter, int cCenter, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    int i, j;
    int mallocSize = rows * cols;
    (*returnColumnSizes) = (int*)malloc(mallocSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal = (int**)malloc(mallocSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (i = 0; i < mallocSize; ++i) {
        (*returnColumnSizes)[i] = 2;
        pRetVal[i] = (int*)malloc(2 * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            pRetVal[(*returnSize)][0] = i;
            pRetVal[(*returnSize)][1] = j;
            (*returnSize)++;
        }
    }
    _rCenter = rCenter;
    _cCenter = cCenter;
    qsort(pRetVal, mallocSize, sizeof(int*), compareIntArray);

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int rows;
        int cols;
        int rCenter;
        int cCenter;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{1, 2, 0, 0, 0, NULL}, {2, 2, 0, 1, 0, NULL}, {2, 3, 1, 2, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: rows = 1, cols = 2, rCenter = 0, cCenter = 0
     *  Output: [[0,0],[0,1]]
     *
     *  Input: rows = 2, cols = 2, rCenter = 0, cCenter = 1
     *  Output: [[0,1],[0,0],[1,1],[1,0]]
     *
     *  Input: rows = 2, cols = 3, rCenter = 1, cCenter = 2
     *  Output: [[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: rows = %d, cols = %d, rCenter = %d, cCenter = %d\n", testCase[i].rows, testCase[i].cols,
               testCase[i].rCenter, testCase[i].cCenter);

        pAnswer = allCellsDistOrder(testCase[i].rows, testCase[i].cols, testCase[i].rCenter, testCase[i].cCenter,
                                    &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
