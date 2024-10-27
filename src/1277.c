#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSquares(int** matrix, int matrixSize, int* matrixColSize) {
    int retVal = 0;

    int row = matrixSize;
    int col = matrixColSize[0];
    int dp[row + 1][col + 1];
    memset(dp, 0, sizeof(dp));
    int x, y;
    for (x = 0; x < row; ++x) {
        for (y = 0; y < col; ++y) {
            if (matrix[x][y] == 0) {
                continue;
            }
            dp[x + 1][y + 1] = fmin(fmin(dp[x][y + 1], dp[x + 1][y]), dp[x][y]) + 1;
            retVal += dp[x + 1][y + 1];
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        int matrix[MAX_SIZE][MAX_SIZE];
        int matrixSize;
        int matrixColSize[MAX_SIZE];
    } testCase[] = {{{{0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}}, 3, {4, 4, 4}},
                    {{{1, 0, 1}, {1, 1, 0}, {1, 1, 0}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[0,1,1,1], [1,1,1,1], [0,1,1,1]]
     *  Output: 15
     *
     *  Input: matrix = [[1,0,1], [1,1,0], [1,1,0]]
     *  Output: 7
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
        answer = countSquares(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize);

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
