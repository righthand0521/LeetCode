#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* luckyNumbers(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(matrixSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (matrixSize * sizeof(int)));

    int rowSize = matrixSize;
    int colSize;
    int value;
    int luckyIndex, luckyValue;
    int row, col, x;
    for (row = 0; row < rowSize; ++row) {
        luckyIndex = 0;
        luckyValue = matrix[row][luckyIndex];

        colSize = matrixColSize[row];
        for (col = 0; col < colSize; ++col) {
            value = matrix[row][col];
            if (value < luckyValue) {
                luckyIndex = col;
                luckyValue = value;
            }
        }

        for (x = 0; x < rowSize; ++x) {
            if (matrix[x][luckyIndex] > luckyValue) {
                luckyIndex = -1;
                break;
            }
        }

        if (luckyIndex != -1) {
            pRetVal[(*returnSize)] = luckyValue;
            (*returnSize) += 1;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (50)
#define MAX_COLUMN (50)
    struct testCaseType {
        int matrix[MAX_ROW][MAX_COLUMN];
        int matrixSize;
        int matrixColSize[MAX_ROW];
        int returnSize;
    } testCase[] = {{{{3, 7, 8}, {9, 11, 13}, {15, 16, 17}}, 3, {3, 3, 3}, 0},
                    {{{1, 10, 4, 2}, {9, 3, 8, 7}, {15, 16, 17, 12}}, 3, {4, 4, 4}, 0},
                    {{{7, 8}, {1, 2}}, 2, {2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
     *  Output: [15]
     *
     *  Input: matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]]
     *  Output: [12]
     *
     *  Input: matrix = [[7,8],[1,2]]
     *  Output: [7]
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
        pAnswer = luckyNumbers(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize, &testCase[i].returnSize);
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
