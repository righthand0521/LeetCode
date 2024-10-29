#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxMoves(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int x, y;

    int row = gridSize;
    int col = gridColSize[0];
    int dp[row][col];
    memset(dp, 0, sizeof(dp));
    for (x = 0; x < row; ++x) {  // Initialize the first column with moves as 1.
        dp[x][0] = 1;
    }

    // Check all three possible previous cells: (x, y-1), (x-1, y-1), (x+1, y-1)
    for (y = 1; y < col; ++y) {
        for (x = 0; x < row; ++x) {
            if ((grid[x][y] > grid[x][y - 1]) && (dp[x][y - 1] > 0)) {
                dp[x][y] = fmax(dp[x][y], dp[x][y - 1] + 1);
            }

            if ((x - 1 >= 0) && (grid[x][y] > grid[x - 1][y - 1]) && (dp[x - 1][y - 1] > 0)) {
                dp[x][y] = fmax(dp[x][y], dp[x - 1][y - 1] + 1);
            }

            if ((x + 1 < row) && (grid[x][y] > grid[x + 1][y - 1]) && (dp[x + 1][y - 1] > 0)) {
                dp[x][y] = fmax(dp[x][y], dp[x + 1][y - 1] + 1);
            }

            retVal = fmax(retVal, dp[x][y] - 1);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (1000)
#define MAX_COLUMN (1000)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {{{{2, 4, 3, 5}, {5, 4, 9, 3}, {3, 4, 2, 11}, {10, 9, 13, 15}}, 4, {4, 4, 4, 4}},
                    {{{3, 2, 4}, {2, 1, 9}, {1, 1, 7}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
     *  Output: 3
     *
     *  Input: grid = [[3,2,4],[2,1,9],[1,1,7]]
     *  Output: 0
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
        answer = maxMoves(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
