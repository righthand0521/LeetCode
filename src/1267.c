#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countServers(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    int rowCounts[colSize];
    memset(rowCounts, 0, sizeof(rowCounts));
    int colCounts[rowSize];
    memset(colCounts, 0, sizeof(colCounts));
    for (int row = 0; row < rowSize; ++row)
        for (int col = 0; col < colSize; ++col)
            if (grid[row][col] == 1) {  // grid[i][j] == 0 or 1
                rowCounts[col]++;
                colCounts[row]++;
            }

    for (int row = 0; row < rowSize; ++row) {
        for (int col = 0; col < colSize; ++col) {
            if (grid[row][col] == 1) {  // grid[i][j] == 0 or 1
                retVal += ((rowCounts[col] > 1) || (colCounts[row] > 1));
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (250)
#define MAX_COLUMN (250)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {{{{1, 0}, {0, 1}}, 2, {2, 2}},
                    {{{1, 0}, {1, 1}}, 2, {2, 2}},
                    {{{1, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}, 4, {4, 4, 4, 4}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,0],[0,1]]
     *  Output: 0
     *
     *  Input: grid = [[1,0],[1,1]]
     *  Output: 3
     *
     *  Input: grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
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
        answer = countServers(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
