#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minFallingPathSum(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int i, j, k;

    int dp[gridSize][gridSize];
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridSize; ++j) {
            dp[i][j] = INT_MAX;
        }
    }
    for (i = 0; i < gridSize; ++i) {
        dp[0][i] = grid[0][i];
    }

    for (i = 1; i < gridSize; ++i) {
        for (j = 0; j < gridSize; ++j) {
            for (k = 0; k < gridSize; ++k) {
                if (j == k) {
                    continue;
                }
                dp[i][j] = fmin(dp[i][j], dp[i - 1][k] + grid[i][j]);
            }
        }
    }

    retVal = dp[gridSize - 1][0];
    for (i = 1; i < gridSize; ++i) {
        retVal = fmin(retVal, dp[gridSize - 1][i]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 3, {3, 3, 3}}, {{{7}}, 1, {1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
     *  Output: 13
     *
     *  Input: grid = [[7]]
     *  Output: 7
     */

    int** pGrid = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].gridColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].grid[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pGrid = (int**)malloc(testCase[i].gridSize * sizeof(int*));
        if (pGrid == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].gridSize; ++j) {
            pGrid[j] = (int*)malloc(testCase[i].gridColSize[j] * sizeof(int));
            if (pGrid[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pGrid[k]) {
                        free(pGrid[k]);
                        pGrid[k] = NULL;
                    }
                }
                free(pGrid);
                pGrid = NULL;
                return EXIT_FAILURE;
            }
            memset(pGrid[j], 0, testCase[i].gridColSize[j] * sizeof(int));
            memcpy(pGrid[j], testCase[i].grid[j], testCase[i].gridColSize[j] * sizeof(int));
        }
        answer = minFallingPathSum(pGrid, testCase[i].gridSize, testCase[i].gridColSize);

        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].gridSize; ++j) {
            if (pGrid[j]) {
                free(pGrid[j]);
                pGrid[j] = NULL;
            }
        }
        free(pGrid);
        pGrid = NULL;
    }

    return EXIT_SUCCESS;
}
