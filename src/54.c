#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    int* pRetVal = NULL;

    int maxReturnSize = matrixSize * matrixColSize[0];
    (*returnSize) = maxReturnSize;
    pRetVal = (int*)calloc((*returnSize), sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    int i, j;
    (*returnSize) = 0;
    for (i = 0; i <= matrixSize / 2; ++i) {
        /* first row: x1, last column: x2, last row: x3, first column: x4.
         *
         *  (top,left)               (top,right)
         *      +------------------------+
         *      | 11 | 11 | 11 | 11 | 11 |
         *      | 14 | 21 | 21 | 21 | 12 |
         *      | 14 | 24 | 31 | 22 | 12 |
         *      | 14 | 23 | 23 | 22 | 12 |
         *      | 13 | 13 | 13 | 13 | 12 |
         *      +------------------------+
         * (down,left)              (down,right)
         */

        // first row
        for (j = i; j < matrixColSize[i] - i; ++j) {
            pRetVal[(*returnSize)++] = matrix[i][j];
            if (((*returnSize)) == maxReturnSize) {
                return pRetVal;
            }
        }
        if (i + 1 == matrixSize - i) {
            continue;
        }

        // last column
        for (j = i + 1; j < matrixSize - i; ++j) {
            pRetVal[(*returnSize)++] = matrix[j][matrixColSize[i] - 1 - i];
            if (((*returnSize)) == maxReturnSize) {
                return pRetVal;
            }
        }
        if (i + 1 == matrixColSize[i]) {
            continue;
        }

        // last row
        for (j = matrixColSize[i] - 1 - (i + 1); j >= i; --j) {
            pRetVal[(*returnSize)++] = matrix[matrixSize - 1 - i][j];
            if (((*returnSize)) == maxReturnSize) {
                return pRetVal;
            }
        }

        // first column
        for (j = matrixSize - 1 - (i + 1); j > i; --j) {
            pRetVal[(*returnSize)++] = matrix[j][i];
            if (((*returnSize)) == maxReturnSize) {
                return pRetVal;
            }
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (10)
#define MAX_COLUMN (10)
    struct testCaseType {
        int matrix[MAX_ROW][MAX_COLUMN];
        int matrixSize;
        int matrixColSize[MAX_ROW];
        int returnSize;
    } testCase[] = {{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 3, {3, 3, 3}, 0},
                    {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}, 3, {4, 4, 4}, 0},
                    {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}, 4, {4, 4, 4, 4}, 0},
                    {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}}, 4, {3, 3, 3, 3}, 0},
                    {{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}, 1, {10}, 0},
                    {{{1, 2, 3, 4, 5, 6, 7, 8, 9}}, 1, {9}, 0},
                    {{{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}}, 10, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 0},
                    {{{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}}, 9, {1, 1, 1, 1, 1, 1, 1, 1, 1}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
     *  Output: [1,2,3,6,9,8,7,4,5]
     *
     *  Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
     *  Output: [1,2,3,4,8,12,11,10,9,5,6,7]
     *
     *  Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]
     *  Output: [1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10]
     *
     *  Input: matrix = [[1,2,3],[4,5,6],[7,8,9],[10,11,12]]
     *  Output: [1,2,3,6,9,12,11,10,7,4,5,8]
     *
     *  Input: matrix = [[1,2,3,4,5,6,7,8,9,10]]
     *  Output: [1,2,3,4,5,6,7,8,9,10]
     *
     *  Input: matrix = [[1,2,3,4,5,6,7,8,9]]
     *  Output: [1,2,3,4,5,6,7,8,9]
     *
     *  Input: matrix = [[1],[2],[3],[4],[5],[6],[7],[8],[9],[10]]
     *  Output: [1,2,3,4,5,6,7,8,9,10]
     *
     *  Input: matrix = [[1],[2],[3],[4],[5],[6],[7],[8],[9]]
     *  Output: [1,2,3,4,5,6,7,8,9]
     */

    int** pMatrix = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: matrix = [");
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].matrixColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].matrix[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pMatrix = (int**)malloc(testCase[i].matrixSize * sizeof(int*));
        if (pMatrix == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            pMatrix[j] = (int*)malloc(testCase[i].matrixColSize[j] * sizeof(int));
            if (pMatrix[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pMatrix[k]);
                }
                free(pMatrix);
                return EXIT_FAILURE;
            }
            memset(pMatrix[j], 0, (testCase[i].matrixColSize[j] * sizeof(int)));
            memcpy(pMatrix[j], testCase[i].matrix[j], (testCase[i].matrixColSize[j] * sizeof(int)));
        }
        pAnswer = spiralOrder(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            free(pMatrix[j]);
        }
        free(pMatrix);
        pMatrix = NULL;
    }

    return EXIT_SUCCESS;
}
