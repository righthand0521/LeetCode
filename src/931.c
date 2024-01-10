#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minFallingPathSum(int** matrix, int matrixSize, int* matrixColSize) {
    int retVal = 0;

    int left, middle, right;
    int row, col;
    for (row = 1; row < matrixSize; ++row) {
        for (col = 0; col < matrixColSize[row]; ++col) {
            left = ((col - 1 >= 0) ? matrix[row - 1][col - 1] : INT_MAX);
            middle = matrix[row - 1][col];
            right = ((col + 1 < matrixColSize[row]) ? matrix[row - 1][col + 1] : INT_MAX);

            matrix[row][col] += fmin(fmin(left, middle), right);
        }
    }

    retVal = matrix[matrixSize - 1][0];
    for (col = 1; col < matrixColSize[matrixSize - 1]; ++col) {
        retVal = fmin(retVal, matrix[matrixSize - 1][col]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int matrix[MAX_SIZE][MAX_SIZE];
        int matrixSize;
        int matrixColSize[MAX_SIZE];
    } testCase[] = {{{{2, 1, 3}, {6, 5, 4}, {7, 8, 9}}, 3, {3, 3, 3}}, {{{-19, 57}, {-40, -5}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
     *  Output: 13
     *
     *  Input: matrix = [[-19,57],[-40,-5]]
     *  Output: -59
     */

    int** pMatrix = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: matrix = [");
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].matrixColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].matrix[j][k]);
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
                    if (pMatrix[k]) {
                        free(pMatrix[k]);
                        pMatrix[k] = NULL;
                    }
                }
                free(pMatrix);
                pMatrix = NULL;
                return EXIT_FAILURE;
            }
            memset(pMatrix[j], 0, testCase[i].matrixColSize[j] * sizeof(int));
            memcpy(pMatrix[j], testCase[i].matrix[j], testCase[i].matrixColSize[j] * sizeof(int));
        }
        answer = minFallingPathSum(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize);

        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].matrixSize; ++j) {
            if (pMatrix[j]) {
                free(pMatrix[j]);
                pMatrix[j] = NULL;
            }
        }
        free(pMatrix);
        pMatrix = NULL;
    }

    return EXIT_SUCCESS;
}
