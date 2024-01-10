#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int dfs(int** grid, int gridSize, int gridColSize, int** dp, int i, int j) {
    int retVal = 1;

    if (dp[i][j] != 0) {
        retVal = dp[i][j];
        return retVal;
    }

    const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int prev_i, prev_j;
    int dir;
    for (dir = 0; dir < 4; ++dir) {
        prev_i = i + directions[dir][0];
        prev_j = j + directions[dir][1];

        if ((prev_i < 0) || (prev_i >= gridSize)) {
            continue;
        } else if ((prev_j < 0) || (prev_j >= gridColSize)) {
            continue;
        } else if (grid[prev_i][prev_j] >= grid[i][j]) {
            continue;
        }
        retVal = (retVal + dfs(grid, gridSize, gridColSize, dp, prev_i, prev_j)) % MODULO;
    }
    dp[i][j] = retVal;

    return retVal;
}
int countPaths(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int i, j;

    //
    int** dp = (int**)malloc(gridSize * sizeof(int*));
    if (dp == NULL) {
        perror("malloc");
        return retVal;
    }
    for (i = 0; i < gridSize; ++i) {
        dp[i] = (int*)malloc(gridColSize[i] * sizeof(int));
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
        memset(dp[i], 0, (gridColSize[i] * sizeof(int)));
    }

    //
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridColSize[0]; ++j) {
            retVal = (retVal + dfs(grid, gridSize, gridColSize[0], dp, i, j)) % MODULO;
        }
    }

    //
    for (i = 0; i < gridSize; ++i) {
        free(dp[i]);
        dp[i] = NULL;
    }
    free(dp);
    dp = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (1000)
#define MAX_COLUMN (1000)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {{{{1, 1}, {3, 4}}, 2, {2, 2}}, {{{1}, {2}}, 2, {1, 1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,1],[3,4]]
     *  Output: 8
     *
     *  Input: grid = [[1],[2]]
     *  Output: 3
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
        answer = countPaths(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
