#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(char** grid, int rowSize, int colSize, int x, int y) {
    grid[x][y] = '0';

    if ((x - 1 >= 0) && (grid[x - 1][y] == '1')) {
        dfs(grid, rowSize, colSize, x - 1, y);
    }
    if ((x + 1 < rowSize) && (grid[x + 1][y] == '1')) {
        dfs(grid, rowSize, colSize, x + 1, y);
    }
    if ((y - 1 >= 0) && (grid[x][y - 1] == '1')) {
        dfs(grid, rowSize, colSize, x, y - 1);
    }
    if ((y + 1 < colSize) && (grid[x][y + 1] == '1')) {
        dfs(grid, rowSize, colSize, x, y + 1);
    }
}
int numIslands(char** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int x, y;
    for (x = 0; x < gridSize; x++) {
        for (y = 0; y < gridColSize[x]; y++) {
            if (grid[x][y] == '0') {
                continue;
            }
            retVal++;
            dfs(grid, gridSize, gridColSize[x], x, y);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        char grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {
        {{{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}},
         4,
         {5, 5, 5, 5}},
        {{{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}},
         4,
         {5, 5, 5, 5}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [
     *    ["1","1","1","1","0"],
     *    ["1","1","0","1","0"],
     *    ["1","1","0","0","0"],
     *    ["0","0","0","0","0"]
     *  ]
     *  Output: 1
     *
     *  Input: grid = [
     *    ["1","1","0","0","0"],
     *    ["1","1","0","0","0"],
     *    ["0","0","1","0","0"],
     *    ["0","0","0","1","1"]
     *  ]
     *  Output: 3
     */

    char** pGrid = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [\n");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("%s  [", (j == 0 ? "" : ",\n"));
            for (k = 0; k < testCase[i].gridColSize[j]; ++k) {
                printf("%s\"%c\"", (k == 0 ? "" : ","), testCase[i].grid[j][k]);
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
        answer = numIslands(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
