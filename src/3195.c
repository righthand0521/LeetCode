#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumArea(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    int minRow = rowSize;
    int maxRow = 0;
    int minCol = colSize;
    int maxCol = 0;
    for (int x = 0; x < rowSize; x++) {
        for (int y = 0; y < colSize; y++) {
            if (grid[x][y] == 1) {
                minRow = fmin(minRow, x);
                maxRow = fmax(maxRow, x);
                minCol = fmin(minCol, y);
                maxCol = fmax(maxCol, y);
            }
        }
    }
    retVal = (maxRow - minRow + 1) * (maxCol - minCol + 1);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (1000)
#define MAX_COLUMN (1000)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {{{{0, 1, 0}, {1, 0, 1}}, 2, {3, 3}}, {{{1, 0}, {0, 0}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,1,0],[1,0,1]]
     *  Output: 6
     *
     *  Input: grid = [[1,0],[0,0]]
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
        answer = minimumArea(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
