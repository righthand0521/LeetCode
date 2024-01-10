#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dfs(int** matrix, int matrixSize, int matrixColSize, int row, int column, int** dp) {
    int retVal = 0;

    if (dp[row][column] != 0) {
        retVal = dp[row][column];
        return retVal;
    }

    const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    ++dp[row][column];
    int x, y;
    int dir;
    for (dir = 0; dir < 4; ++dir) {
        x = row + directions[dir][0];
        y = column + directions[dir][1];

        if ((x < 0) || (x >= matrixSize)) {
            continue;
        } else if ((y < 0) || (y >= matrixColSize)) {
            continue;
        } else if (matrix[x][y] <= matrix[row][column]) {
            continue;
        }
        dp[row][column] = fmax(dp[row][column], dfs(matrix, matrixSize, matrixColSize, x, y, dp) + 1);
    }
    retVal = dp[row][column];

    return retVal;
}
int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize) {
    int retVal = 0;

    if ((matrixSize == 0) || (matrixColSize == 0)) {
        return retVal;
    }

    //
    int i, j;
    int** dp = (int**)malloc(matrixSize * sizeof(int*));
    if (dp == NULL) {
        perror("malloc");
        return retVal;
    }
    for (i = 0; i < matrixSize; ++i) {
        dp[i] = (int*)malloc(matrixColSize[i] * sizeof(int));
        if (dp[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(dp[j]);
                dp[j] = NULL;
            }
            free(dp);
            dp = NULL;
            return retVal;
        }
        memset(dp[i], 0, (matrixColSize[i] * sizeof(int)));
    }

    //
    int x, y;
    for (x = 0; x < matrixSize; ++x) {
        for (y = 0; y < matrixColSize[x]; ++y) {
            retVal = fmax(retVal, dfs(matrix, matrixSize, matrixColSize[0], x, y, dp));
        }
    }

    //
    for (i = 0; i < matrixSize; ++i) {
        free(dp[i]);
        dp[i] = NULL;
    }
    free(dp);
    dp = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (200)
#define MAX_COLUMN (200)
    struct testCaseType {
        int matrix[MAX_ROW][MAX_COLUMN];
        int matrixSize;
        int matrixColSize[MAX_ROW];
    } testCase[] = {{{{9, 9, 4}, {6, 6, 8}, {2, 1, 1}}, 3, {3, 3, 3}},
                    {{{3, 4, 5}, {3, 2, 6}, {2, 2, 1}}, 3, {3, 3, 3}},
                    {{{1}}, 1, {1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
     *  Output: 4
     *
     *  Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
     *  Output: 4
     *
     *  Input: matrix = [[1]]
     *  Output: 1
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
                    free(pMatrix[k]);
                    pMatrix[k] = NULL;
                }
                free(pMatrix);
                pMatrix = NULL;
                return EXIT_FAILURE;
            }
            memset(pMatrix[j], 0, testCase[i].matrixColSize[j] * sizeof(int));
            memcpy(pMatrix[j], testCase[i].matrix[j], testCase[i].matrixColSize[j] * sizeof(int));
        }
        answer = longestIncreasingPath(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].matrixSize; ++j) {
            free(pMatrix[j]);
            pMatrix[j] = NULL;
        }
        free(pMatrix);
        pMatrix = NULL;
    }

    return EXIT_SUCCESS;
}
