#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool dfs(int** grid, int gridSize, int* gridColSize, int x, int y) {
    bool retVal = false;

    int row = gridSize;
    int col = gridColSize[0];

    if ((x < 0) || (x >= row) || (y < 0) || (y >= col)) {
        return retVal;
    }

    if (grid[x][y] == true) {
        retVal = true;
        return retVal;
    }

    grid[x][y] = 1;

    bool up = dfs(grid, gridSize, gridColSize, x - 1, y);
    bool down = dfs(grid, gridSize, gridColSize, x + 1, y);
    bool left = dfs(grid, gridSize, gridColSize, x, y - 1);
    bool right = dfs(grid, gridSize, gridColSize, x, y + 1);
    retVal = up && down && left && right;

    return retVal;
}
int closedIsland(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int row = gridSize;
    int col = gridColSize[0];

    int x, y;
    for (x = 1; x < row; ++x) {
        for (y = 1; y < col; ++y) {
            if (grid[x][y] != 0) {
                continue;
            }

            if (dfs(grid, gridSize, gridColSize, x, y) == true) {
                ++retVal;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{1, 1, 1, 1, 1, 1, 1, 0},
                      {1, 0, 0, 0, 0, 1, 1, 0},
                      {1, 0, 1, 0, 1, 1, 1, 0},
                      {1, 0, 0, 0, 0, 1, 0, 1},
                      {1, 1, 1, 1, 1, 1, 1, 0}},
                     5,
                     {8, 8, 8, 8, 8}},
                    {{{0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {0, 1, 1, 1, 0}}, 3, {5, 5, 5}},
                    {{{1, 1, 1, 1, 1, 1, 1},
                      {1, 0, 0, 0, 0, 0, 1},
                      {1, 0, 1, 1, 1, 0, 1},
                      {1, 0, 1, 0, 1, 0, 1},
                      {1, 0, 1, 1, 1, 0, 1},
                      {1, 0, 0, 0, 0, 0, 1},
                      {1, 1, 1, 1, 1, 1, 1}},
                     7,
                     {7, 7, 7, 7, 7, 7, 7}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,1,1,1,1,1,1,0],
     *                 [1,0,0,0,0,1,1,0],
     *                 [1,0,1,0,1,1,1,0],
     *                 [1,0,0,0,0,1,0,1],
     *                 [1,1,1,1,1,1,1,0]]
     *  Output: 2
     *
     *  Input: grid = [[0,0,1,0,0],
     *                 [0,1,0,1,0],
     *                 [0,1,1,1,0]]
     *  Output: 1
     *
     *  Input: grid = [[1,1,1,1,1,1,1],
     *                 [1,0,0,0,0,0,1],
     *                 [1,0,1,1,1,0,1],
     *                 [1,0,1,0,1,0,1],
     *                 [1,0,1,1,1,0,1],
     *                 [1,0,0,0,0,0,1],
     *                 [1,1,1,1,1,1,1]]
     *  Output: 2
     */

    int** pGrid = NULL;
    int answer;
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
                    free(pGrid[j]);
                    pGrid[j] = NULL;
                }
                return EXIT_FAILURE;
            }
            memset(pGrid[j], 0, (testCase[i].gridColSize[j] * sizeof(int)));
            memcpy(pGrid[j], testCase[i].grid[j], (testCase[i].gridColSize[j] * sizeof(int)));
        }
        answer = closedIsland(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
