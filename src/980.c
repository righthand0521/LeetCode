#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(int** grid, int gridSize, int* gridColSize, int* pathNum, int* zeroNum, int t, int x, int y) {
    if ((x < 0) || (x >= gridSize) || (y < 0) || (y >= gridColSize[0])) {
        return;
    }

    if ((grid[x][y] == 2) && (t != (*zeroNum))) {
        return;
    }

    if ((grid[x][y] == 2) && (t == (*zeroNum))) {
        (*pathNum)++;
        return;
    }

    if (grid[x][y] == -1) {
        return;
    }

    int temp = grid[x][y];
    grid[x][y] = -1;
    dfs(grid, gridSize, gridColSize, pathNum, zeroNum, t + 1, x - 1, y);
    dfs(grid, gridSize, gridColSize, pathNum, zeroNum, t + 1, x + 1, y);
    dfs(grid, gridSize, gridColSize, pathNum, zeroNum, t + 1, x, y + 1);
    dfs(grid, gridSize, gridColSize, pathNum, zeroNum, t + 1, x, y - 1);
    grid[x][y] = temp;
}
int uniquePathsIII(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int pathNum = 0;
    int zeroNum = 0;
    int x = 0;
    int y = 0;
    int i, j;
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridColSize[0]; ++j) {
            if (grid[i][j] == 0) {
                ++zeroNum;
            }
            if (grid[i][j] == 1) {
                x = i;
                y = j;
            }
        }
    }
    dfs(grid, gridSize, gridColSize, &pathNum, &zeroNum, -1, x, y);

    retVal = pathNum;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1}}, 3, {4, 4, 4}},
                    {{{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 2}}, 3, {4, 4, 4}},
                    {{{0, 1}, {2, 0}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pGrid = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].gridColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].grid[j][k]);
            }
            printf("]");
        }
        printf("]\n");

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
        answer = uniquePathsIII(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
