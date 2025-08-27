#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int directions[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
int dfs(int** grid, int gridSize, int gridColSize, int*** memo, int x, int y, int z, int turn, int target) {
    int retVal = 0;

    x += directions[z][0];
    y += directions[z][1];
    if ((x < 0) || (x >= gridSize) || (y < 0) || (y >= gridColSize)) {
        return retVal;
    } else if (grid[x][y] != target) {
        return retVal;
    }

    int maxs[4];
    int next;
    int mask = (z << 1) | turn;
    if (memo[x][y][mask] <= 0) {
        retVal = dfs(grid, gridSize, gridColSize, memo, x, y, z, turn, 2 - target);
        if (turn == 1) {
            memset(maxs, 0, sizeof(maxs));
            maxs[0] = gridSize - x - 1;
            maxs[1] = y;
            maxs[2] = x;
            maxs[3] = gridColSize - y - 1;
            next = (z + 1) % 4;
            if (maxs[next] > retVal) {
                retVal = fmax(retVal, dfs(grid, gridSize, gridColSize, memo, x, y, next, 0, 2 - target));
            }
        }
        memo[x][y][mask] = retVal + 1;
    }
    retVal = memo[x][y][mask];

    return retVal;
}
int lenOfVDiagonal(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];
    int depth = (1 << 3);

    int*** memo = (int***)malloc(rowSize * sizeof(int**));
    for (int i = 0; i < rowSize; i++) {
        memo[i] = (int**)malloc(colSize * sizeof(int*));
        for (int j = 0; j < colSize; j++) {
            memo[i][j] = (int*)malloc(depth * sizeof(int));
            memset(memo[i][j], -1, depth * sizeof(int));
        }
    }

    for (int x = 0; x < rowSize; ++x) {
        for (int y = 0; y < colSize; ++y) {
            if (grid[x][y] != 1) {
                continue;
            }

            int maxs[4] = {rowSize - x, y + 1, x + 1, colSize - y};
            for (int z = 0; z < 4; ++z) {
                if (maxs[z] > retVal) {
                    retVal = fmax(retVal, dfs(grid, rowSize, colSize, memo, x, y, z, 1, 2) + 1);
                }
            }
        }
    }

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            free(memo[i][j]);
            memo[i][j] = NULL;
        }
        free(memo[i]);
        memo[i] = NULL;
    }
    free(memo);
    memo = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (500)
#define MAX_COLUMN (500)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {
        {{{2, 2, 1, 2, 2}, {2, 0, 2, 2, 0}, {2, 0, 1, 1, 0}, {1, 0, 2, 2, 2}, {2, 0, 0, 2, 2}}, 5, {5, 5, 5, 5, 5}},
        {{{2, 2, 2, 2, 2}, {2, 0, 2, 2, 0}, {2, 0, 1, 1, 0}, {1, 0, 2, 2, 2}, {2, 0, 0, 2, 2}}, 5, {5, 5, 5, 5, 5}},
        {{{1, 2, 2, 2, 2}, {2, 2, 2, 2, 0}, {2, 0, 0, 0, 0}, {0, 0, 2, 2, 2}, {2, 0, 0, 2, 0}}, 5, {5, 5, 5, 5, 5}},
        {{{1}}, 1, {1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
     *  Output: 5
     *
     *  Input: grid = [[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
     *  Output: 4
     *
     *  Input: grid = [[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]]
     *  Output: 5
     *
     *  Input: grid = [[1]]
     *  Output: 1
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
        answer = lenOfVDiagonal(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
