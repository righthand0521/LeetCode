#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long maxMatrixSum(int** matrix, int matrixSize, int* matrixColSize) {
    long long retVal = 0;

    int minAbsVal = INT_MAX;
    int negativeCount = 0;
    int row, col, value;
    for (row = 0; row < matrixSize; ++row) {
        for (col = 0; col < matrixColSize[row]; ++col) {
            value = matrix[row][col];
            retVal += abs(value);
            if (value < 0) {
                negativeCount++;
            }
            minAbsVal = fmin(minAbsVal, abs(value));
        }
    }

    if (negativeCount % 2 != 0) {
        retVal -= (2 * minAbsVal);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (250)
    struct testCaseType {
        int matrix[MAX_SIZE][MAX_SIZE];
        int matrixSize;
        int matrixColSize[MAX_SIZE];
    } testCase[] = {{{{1, -1}, {-1, 1}}, 2, {2, 2}}, {{{1, 2, 3}, {-1, -2, -3}, {1, 2, 3}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[1,-1],[-1,1]]
     *  Output: 4
     *
     *  Input: matrix = [[1,2,3],[-1,-2,-3],[1,2,3]]
     *  Output: 16
     */

    int** pMatrix = NULL;
    long long answer = 0;
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
        answer = maxMatrixSum(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize);
        printf("Output: %lld\n", answer);

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
