#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int largestMagicSquare(int** grid, int gridSize, int* gridColSize) {
    int retVal = 1;

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    // prefix sum of each row
    int rowsum[rowSize][colSize];
    for (int i = 0; i < rowSize; ++i) {
        rowsum[i][0] = grid[i][0];
        for (int j = 1; j < colSize; ++j) {
            rowsum[i][j] = rowsum[i][j - 1] + grid[i][j];
        }
    }
    // prefix sum of each column
    int colsum[rowSize][colSize];
    for (int j = 0; j < colSize; ++j) {
        colsum[0][j] = grid[0][j];
        for (int i = 1; i < rowSize; ++i) {
            colsum[i][j] = colsum[i - 1][j] + grid[i][j];
        }
    }

    int min_edge = rowSize < colSize ? rowSize : colSize;
    // enumerate edge lengths from largest to smallest
    for (int edge = min_edge; edge >= 2; --edge) {
        // enumerate the top-left corner position (i,j) of the square
        for (int i = 0; i + edge <= rowSize; ++i) {
            for (int j = 0; j + edge <= colSize; ++j) {
                // calculate the standard value
                int stdsum = rowsum[i][j + edge - 1] - (j > 0 ? rowsum[i][j - 1] : 0);
                int check = 1;

                // check each row
                for (int ii = i + 1; ii < i + edge; ++ii) {
                    int sum = rowsum[ii][j + edge - 1] - (j > 0 ? rowsum[ii][j - 1] : 0);
                    if (sum != stdsum) {
                        check = 0;
                        break;
                    }
                }
                if (check == 0) {
                    continue;
                }

                // check each column
                for (int jj = j; jj < j + edge; ++jj) {
                    int sum = colsum[i + edge - 1][jj] - (i > 0 ? colsum[i - 1][jj] : 0);
                    if (sum != stdsum) {
                        check = 0;
                        break;
                    }
                }
                if (check == 0) {
                    continue;
                }

                // check the diagonal
                int d1 = 0;
                int d2 = 0;
                for (int k = 0; k < edge; ++k) {
                    d1 += grid[i + k][j + k];
                    d2 += grid[i + k][j + edge - 1 - k];
                }
                if ((d1 == stdsum) && (d2 == stdsum)) {
                    retVal = edge;
                    return retVal;
                }
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (50)
#define MAX_COLUMN (50)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {{{{7, 1, 4, 5, 6}, {2, 5, 1, 6, 4}, {1, 5, 4, 3, 2}, {1, 2, 7, 3, 4}}, 4, {5, 5, 5, 5}},
                    {{{5, 1, 3, 1}, {9, 3, 3, 1}, {1, 3, 3, 8}}, 3, {4, 4, 4}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
     *  Output: 3
     *
     *  Input: grid = [[5,1,3,1],[9,3,3,1],[1,3,3,8]]
     *  Output: 2
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
        answer = largestMagicSquare(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
