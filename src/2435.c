#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int numberOfPaths(int** grid, int gridSize, int* gridColSize, int k) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];
    long long dp[(rowSize + 1)][(colSize + 1)][k];
    memset(dp, 0, sizeof(dp));

    int value, prevMod;
    for (int i = 1; i <= rowSize; i++) {
        for (int j = 1; j <= colSize; j++) {
            if ((i == 1) && (j == 1)) {
                dp[i][j][grid[0][0] % k] = 1;
                continue;
            }

            value = grid[i - 1][j - 1] % k;
            for (int r = 0; r < k; r++) {
                prevMod = (r - value + k) % k;
                dp[i][j][r] = (dp[i - 1][j][prevMod] + dp[i][j - 1][prevMod]) % MODULO;
            }
        }
    }
    retVal = dp[rowSize][colSize][0];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (int)(1e2)
#define MAX_COLUMN (int)(1e2)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
        int k;
    } testCase[] = {{{{5, 2, 4}, {3, 0, 5}, {0, 7, 2}}, 3, {3, 3, 3}, 3},
                    {{{0, 0}}, 1, {2}, 5},
                    {{{7, 3, 4, 9}, {2, 3, 6, 2}, {2, 3, 7, 0}}, 3, {4, 4, 4}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
     *  Output: 2
     *
     *  Input: grid = [[0,0]], k = 5
     *  Output: 1
     *
     *  Input: grid = [[7,3,4,9],[2,3,6,2],[2,3,7,0]], k = 1
     *  Output: 10
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
        printf("], k = %d\n", testCase[i].k);

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
                    free(pGrid[k]);
                    pGrid[k] = NULL;
                }
                free(pGrid);
                pGrid = NULL;
                return EXIT_FAILURE;
            }
            memset(pGrid[j], 0, testCase[i].gridColSize[j] * sizeof(int));
            memcpy(pGrid[j], testCase[i].grid[j], testCase[i].gridColSize[j] * sizeof(int));
        }
        answer = numberOfPaths(pGrid, testCase[i].gridSize, testCase[i].gridColSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].gridSize; ++j) {
            free(pGrid[j]);
            pGrid[j] = NULL;
        }
        free(pGrid);
        pGrid = NULL;
    }

    return EXIT_SUCCESS;
}
