#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximalSquare(char** matrix, int matrixSize, int* matrixColSize) {
    int retVal = 0;

    // m == matrix.length, n == matrix[i].length, 1 <= m, n <= 300
    if ((matrixSize == 0) || (matrixColSize[0] == 0)) {
        return retVal;
    }

    int dp[matrixSize][matrixColSize[0]];
    memset(dp, 0, sizeof(dp));

    int maxSide = 0;
    int i, j;
    for (i = 0; i < matrixSize; ++i) {
        for (j = 0; j < matrixColSize[0]; ++j) {
            if (matrix[i][j] != '1') {
                continue;
            }

            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = fmin(fmin(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
            }
            maxSide = fmax(maxSide, dp[i][j]);
        }
    }
    retVal = maxSide * maxSide;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        char matrix[MAX_SIZE][MAX_SIZE];
        int matrixSize;
        int matrixColSize[MAX_SIZE];
    } testCase[] = {
        {{{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}},
         4,
         {5, 5, 5, 5}},
        {{{'0', '1'}, {'1', '0'}}, 2, {2, 2}},
        {{{'0'}}, 1, {1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
     *  Output: 4
     *
     *  Input: matrix = [["0","1"],["1","0"]]
     *  Output: 1
     *
     *  Input: matrix = [["0"]]
     *  Output: 0
     */

    char** pMatrix = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: matrix = [");
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].matrixColSize[j]; ++k) {
                printf("%s\"%c\"", (k == 0) ? "" : ",", testCase[i].matrix[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pMatrix = (char**)malloc(testCase[i].matrixSize * sizeof(char*));
        if (pMatrix == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            pMatrix[j] = (char*)malloc(testCase[i].matrixColSize[j] * sizeof(char));
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
            memset(pMatrix[j], 0, testCase[i].matrixColSize[j] * sizeof(char));
            memcpy(pMatrix[j], testCase[i].matrix[j], testCase[i].matrixColSize[j] * sizeof(char));
        }
        answer = maximalSquare(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize);
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
