#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cherryPickup(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];
    int i, j, k;

    int dp[rowSize][colSize][colSize];
    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            for (k = 0; k < colSize; ++k) {
                dp[i][j][k] = -1;
            }
        }
    }
    dp[0][0][colSize - 1] = grid[0][0] + grid[0][colSize - 1];

    int a, b, c, d, e, f, g, h, t, temp;
    for (i = 1; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            for (k = 0; k < colSize; ++k) {
                a = -1;
                if ((i > 0) && (j > 0) && (k > 0)) {
                    a = dp[i - 1][j - 1][k - 1];
                }

                b = -1;
                if ((i > 0) && (j > 0)) {
                    b = dp[i - 1][j - 1][k];
                }

                c = -1;
                if ((i > 0) && (j > 0) && (k + 1 < colSize)) {
                    c = dp[i - 1][j - 1][k + 1];
                }

                d = -1;
                if ((i > 0) && (k > 0)) {
                    d = dp[i - 1][j][k - 1];
                }

                e = -1;
                if (i > 0) {
                    e = dp[i - 1][j][k];
                }

                f = -1;
                if ((i > 0) && (k + 1 < colSize)) {
                    f = dp[i - 1][j][k + 1];
                }

                g = -1;
                if ((i > 0) && (j + 1 < colSize) && (k > 0)) {
                    g = dp[i - 1][j + 1][k - 1];
                }

                h = -1;
                if ((i > 0) && (j + 1 < colSize)) {
                    h = dp[i - 1][j + 1][k];
                }

                t = -1;
                if ((i > 0) && (j + 1 < colSize) && (k + 1 < colSize)) {
                    t = dp[i - 1][j + 1][k + 1];
                }

                temp = fmax(fmax(fmax(fmax(a, b), fmax(c, d)), fmax(fmax(e, f), fmax(g, h))), t);
                if (temp == -1) {
                    dp[i][j][k] = -1;
                } else {
                    if (j == k) {
                        dp[i][j][k] = temp + grid[i][j];
                    } else {
                        dp[i][j][k] = temp + grid[i][j] + grid[i][k];
                    }
                }
            }
        }
    }

    for (i = 0; i < colSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            retVal = fmax(retVal, dp[rowSize - 1][i][j]);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (70)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{3, 1, 1}, {2, 5, 1}, {1, 5, 5}, {2, 1, 1}}, 4, {3, 3, 3, 3}},
                    {{{1, 0, 0, 0, 0, 0, 1},
                      {2, 0, 0, 0, 0, 3, 0},
                      {2, 0, 9, 0, 0, 0, 0},
                      {0, 3, 0, 5, 4, 0, 0},
                      {1, 0, 2, 3, 0, 0, 6}},
                     5,
                     {7, 7, 7, 7, 7}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
     *  Output: 24
     *
     *  Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
     *  Output: 28
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
        answer = cherryPickup(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
