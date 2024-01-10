#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minPathSum(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int i, j;

    // m == grid.length, n == grid[i].length, 1 <= m, n <= 200
    int row = gridSize;
    int col = gridColSize[0];
    int minPathSum[row][col];

    /* Example
     *    | 0 1 2 |  0     1     2
     *  --+-------+------------------
     *  0 | 1 3 1 |   (1) 1+(3) 4+(1)
     *  1 | 1 5 1 | 1+(1) 2+(5) 5+(1)
     *  2 | 4 2 1 | 2+(4) 6+(2) 6+(1)
     */
    minPathSum[0][0] = grid[0][0];
    for (i = 1; i < row; ++i) {
        minPathSum[i][0] = minPathSum[i - 1][0] + grid[i][0];
    }
    for (i = 1; i < col; ++i) {
        minPathSum[0][i] = minPathSum[0][i - 1] + grid[0][i];
    }

    int rowTmp;
    int colTmp;
    for (i = 1; i < row; ++i) {
        for (j = 1; j < col; ++j) {
            rowTmp = minPathSum[i - 1][j] + grid[i][j];
            colTmp = minPathSum[i][j - 1] + grid[i][j];
            minPathSum[i][j] = fmin(rowTmp, colTmp);
        }
    }
    retVal = minPathSum[row - 1][col - 1];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (200)
#define MAX_COLUMN (200)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {{{{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}, 3, {3, 3, 3}}, {{{1, 2, 3}, {4, 5, 6}}, 2, {3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
     *  Output: 7
     *
     *  Input: grid = [[1,2,3],[4,5,6]]
     *  Output: 12
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
        answer = minPathSum(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
