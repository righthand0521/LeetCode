#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isMagicSquare(int** grid, int row, int col) {
    int retVal = 0;

    int seen[10];  // while a magic square can only contain numbers from 1 to 9
    memset(seen, 0, sizeof(seen));

    int x, y, num;
    for (x = 0; x < 3; ++x) {
        for (y = 0; y < 3; ++y) {
            num = grid[row + x][col + y];
            if ((num < 1) || (num > 9)) {
                return retVal;
            } else if (seen[num] != 0) {
                return retVal;
            }
            seen[num] = 1;
        }
    }

    int diagonal1 = grid[row][col] + grid[row + 1][col + 1] + grid[row + 2][col + 2];
    int diagonal2 = grid[row + 2][col] + grid[row + 1][col + 1] + grid[row][col + 2];
    if (diagonal1 != diagonal2) {
        return retVal;
    }

    int row1 = grid[row][col] + grid[row][col + 1] + grid[row][col + 2];
    int row2 = grid[row + 1][col] + grid[row + 1][col + 1] + grid[row + 1][col + 2];
    int row3 = grid[row + 2][col] + grid[row + 2][col + 1] + grid[row + 2][col + 2];
    if ((row1 != diagonal1) || (row2 != diagonal1) || (row3 != diagonal1)) {
        return retVal;
    }

    int col1 = grid[row][col] + grid[row + 1][col] + grid[row + 2][col];
    int col2 = grid[row][col + 1] + grid[row + 1][col + 1] + grid[row + 2][col + 1];
    int col3 = grid[row][col + 2] + grid[row + 1][col + 2] + grid[row + 2][col + 2];
    if ((col1 != diagonal1) || (col2 != diagonal1) || (col3 != diagonal1)) {
        return retVal;
    }

    retVal = 1;

    return retVal;
}
int numMagicSquaresInside(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];  // 1 <= row, col <= 10
    if ((rowSize < 3) || (colSize < 3)) {
        return retVal;
    }

    int x, y;
    for (x = 0; x < rowSize - 2; ++x) {
        for (y = 0; y < colSize - 2; ++y) {
            retVal += isMagicSquare(grid, x, y);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (10)
#define MAX_COLUMN (10)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {{{{4, 3, 8, 4}, {9, 5, 1, 9}, {2, 7, 6, 2}}, 3, {4, 4, 4}}, {{{8}}, 1, {1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[4,3,8,4],[9,5,1,9],[2,7,6,2]]
     *  Output: 1
     *
     *  Input: grid = [[8]]
     *  Output: 0
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
        answer = numMagicSquaresInside(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
