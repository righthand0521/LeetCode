#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int islandPerimeter(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowDirection[4] = {1, -1, 0, 0};
    int colDirection[4] = {0, 0, 1, -1};

    int rowSize = gridSize;
    int colColSize = gridColSize[0];
    int x, y, i, row, col, count;
    for (x = 0; x < rowSize; ++x) {
        for (y = 0; y < colColSize; ++y) {
            if (grid[x][y] == 0) {
                continue;
            }

            count = 0;
            for (i = 0; i < 4; ++i) {
                row = x + rowDirection[i];
                col = y + colDirection[i];
                if ((row < 0) || (row >= rowSize) || (col < 0) || (col >= colColSize)) {
                    count++;
                } else if (grid[row][col] == 0) {
                    count++;
                }
            }
            retVal += count;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (100)
#define MAX_COLUMN (100)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {{{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}}, 4, {4, 4, 4, 4}},
                    {{{1}}, 1, {1}},
                    {{{1, 0}}, 1, {2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
     *  Output: 16
     *
     *  Input: grid = [[1]]
     *  Output: 4
     *
     *  Input: grid = [[1,0]]
     *  Output: 4
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
        answer = islandPerimeter(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
