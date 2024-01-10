#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dfs(int** grid, int x, int y, int rowSize, int colSize) {
    int retVal = 0;

    if ((x < 0) || (x >= rowSize) || (y < 0) || (y >= colSize)) {
        return retVal;
    }

    if (grid[x][y] == 0) {
        return retVal;
    }
    grid[x][y] = 0;
    retVal = 1;
    retVal += dfs(grid, x - 1, y, rowSize, colSize);
    retVal += dfs(grid, x + 1, y, rowSize, colSize);
    retVal += dfs(grid, x, y - 1, rowSize, colSize);
    retVal += dfs(grid, x, y + 1, rowSize, colSize);

    return retVal;
}
int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int area;
    int i, j;
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridColSize[i]; ++j) {
            if (grid[i][j] == 0) {
                continue;
            }
            area = dfs(grid, i, j, gridSize, gridColSize[i]);
            retVal = fmax(retVal, area);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                      {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
                      {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}},
                     8,
                     {13, 13, 13, 13, 13, 13, 13, 13}},
                    {{{0, 0, 0, 0, 0, 0, 0, 0}}, 1, {8}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pGrid = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [\n");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("%s  [", (j == 0 ? "" : ",\n"));
            for (k = 0; k < testCase[i].gridColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].grid[j][k]);
            }
            printf("]");
        }
        printf("\n]\n");

        pGrid = malloc(testCase[i].gridSize * sizeof(int*));
        if (pGrid == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].gridSize; ++j) {
            pGrid[j] = malloc(testCase[i].gridColSize[j] * sizeof(int));
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
            memset(pGrid[j], 0, (testCase[i].gridColSize[j] * sizeof(int)));
            memcpy(pGrid[j], testCase[i].grid[j], (testCase[i].gridColSize[j] * sizeof(int)));
        }
        answer = maxAreaOfIsland(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
