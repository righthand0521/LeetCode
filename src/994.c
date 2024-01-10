#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int orangesRotting(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int fresh = 0;
    int rotten = 0;

    int i, j;
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridColSize[i]; ++j) {
            if (grid[i][j] == 1) {
                ++fresh;
            } else if (grid[i][j] == 2) {
                ++rotten;
            }
        }
    }
    if (fresh == 0) {
        return retVal;
    } else if (rotten == 0) {
        retVal = -1;
        return retVal;
    }

    int remain = fresh;
    while (remain) {
        ++retVal;

        for (i = 0; i < gridSize; ++i) {
            for (j = 0; j < gridColSize[i]; ++j) {
                if (grid[i][j] == 2) {
                    if ((i > 0) && (grid[i - 1][j] == 1)) {
                        grid[i - 1][j] = 3;
                        --remain;
                    }

                    if ((j > 0) && (grid[i][j - 1] == 1)) {
                        grid[i][j - 1] = 3;
                        --remain;
                    }

                    if ((i < gridSize - 1) && (grid[i + 1][j] == 1)) {
                        grid[i + 1][j] = 3;
                        --remain;
                    }

                    if ((j < gridColSize[i] - 1) && (grid[i][j + 1] == 1)) {
                        grid[i][j + 1] = 3;
                        --remain;
                    }
                }
            }
        }

        for (i = 0; i < gridSize; ++i) {
            for (j = 0; j < gridColSize[0]; ++j) {
                if (grid[i][j] == 3) {
                    grid[i][j] = 2;
                }
            }
        }

        if (remain == fresh) {
            retVal = -1;
            return retVal;
        }

        fresh = remain;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}, 3, {3, 3, 3}},
                    {{{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}, 3, {3, 3, 3}},
                    {{{0, 2}}, 1, {2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
     *  Output: 4
     *
     *  Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
     *  Output: -1
     *
     *  Input: grid = [[0,2]]
     *  Output: 0
     */

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
        answer = orangesRotting(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
