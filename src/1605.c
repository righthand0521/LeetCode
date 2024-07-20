#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** restoreMatrix(int* rowSum, int rowSumSize, int* colSum, int colSumSize, int* returnSize,
                    int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    //
    (*returnColumnSizes) = (int*)malloc(rowSumSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    //
    pRetVal = (int**)malloc(rowSumSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for ((*returnSize) = 0; (*returnSize) < rowSumSize; ++(*returnSize)) {
        pRetVal[(*returnSize)] = (int*)malloc(colSumSize * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (int i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(pRetVal[(*returnSize)], 0, (colSumSize * sizeof(int)));
        (*returnColumnSizes)[(*returnSize)] = colSumSize;
    }

    /* rowSum = [5,7,10], colSum = [8,6,8]
     *       8 6 8       3 6 8       0 6 8       0 2 8      0 0 8      0 0 0
     *   --+-------  --+-------  --+-------  --+-------  --+-------  --+-------
     *   5 | 0 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0   0 | 5 0 0
     *   7 | 0 0 0   7 | 0 0 0   4 | 3 0 0   0 | 3 4 0   0 | 3 4 0   0 | 3 4 0
     *  10 | 0 0 0  10 | 0 0 0  10 | 0 0 0  10 | 0 0 0   8 | 0 2 0   0 | 0 2 8
     */
    int x = 0;
    int y = 0;
    while ((x < rowSumSize) && (y < colSumSize)) {
        pRetVal[x][y] = fmin(rowSum[x], colSum[y]);
        rowSum[x] -= pRetVal[x][y];
        colSum[y] -= pRetVal[x][y];
        if (rowSum[x] == 0) {
            x++;
        } else {
            y++;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int rowSum[MAX_SIZE];
        int rowSumSize;
        int colSum[MAX_SIZE];
        int colSumSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{3, 8}, 2, {4, 7}, 2, 0, NULL}, {{5, 7, 10}, 3, {8, 6, 8}, 3, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: rowSum = [3,8], colSum = [4,7]
     *  Output: [[3,0], [1,7]]
     *
     *  Input: rowSum = [5,7,10], colSum = [8,6,8]
     *  Output: [[0,5,0], [6,1,0], [2,0,8]]
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: rowSum = [");
        for (j = 0; j < testCase[i].rowSumSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].rowSum[j]);
        }
        printf("], colSum = [");
        for (j = 0; j < testCase[i].colSumSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].colSum[j]);
        }
        printf("]\n");

        pAnswer = restoreMatrix(testCase[i].rowSum, testCase[i].rowSumSize, testCase[i].colSum, testCase[i].colSumSize,
                                &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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
