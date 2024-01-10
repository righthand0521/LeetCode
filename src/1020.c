#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(int** grid, int gridSize, int* gridColSize, int x, int y) {
    int row = gridSize;
    int col = gridColSize[0];

    if ((x < 0) || (x >= row) || (y < 0) || (y >= col)) {
        return;
    }

    if (grid[x][y] == 0) {
        return;
    }

    grid[x][y] = 0;
    dfs(grid, gridSize, gridColSize, x - 1, y);
    dfs(grid, gridSize, gridColSize, x + 1, y);
    dfs(grid, gridSize, gridColSize, x, y - 1);
    dfs(grid, gridSize, gridColSize, x, y + 1);
}
int numEnclaves(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int row = gridSize;
    int col = gridColSize[0];
    int x, y;
    for (x = 0; x < row; ++x) {
        for (y = 0; y < col; ++y) {
            if ((x != 0) && (x != row - 1) && (y != 0) && (y != col - 1)) {
                continue;
            }

            if (grid[x][y] != 1) {
                continue;
            }

            dfs(grid, gridSize, gridColSize, x, y);
        }
    }

    for (x = 0; x < row; ++x) {
        for (y = 0; y < col; ++y) {
            retVal += grid[x][y];
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{0, 0, 0, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, 4, {4, 4, 4, 4}},
                    {{{0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}, 4, {4, 4, 4, 4}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
     *  Output: 3
     *
     *  Input: grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
     *  Output: 0
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
        answer = numEnclaves(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
