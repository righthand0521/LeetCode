#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int largest1BorderedSquare(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    /* https://leetcode.com/problems/largest-1-bordered-square/solutions/345233/java-c-python-straight-forward/
     *  1. Count the number of consecutive 1s on the top and on the left.
     *  2. From length of edge l = min(m,n) to l = 1, check if the 1-bordered square exist.
     *
     *  Example: grid = [[1,1,1],[1,0,1],[1,1,1]]
     *       +-----------+
     *       | 1 | 1 | 1 |
     *   top | 2 | 0 | 2 |
     *       | 3 | 1 | 3 |
     *       +-----------+
     *         ^   ^   ^
     *       +-----------+    +-----------+
     *       | 1 | 1 | 1 | -> | 1 | 2 | 3 |
     *  grid | 1 | 0 | 1 | -> | 1 | 0 | 1 | left
     *       | 1 | 1 | 1 | -> | 1 | 2 | 3 |
     *       +-----------+    +-----------+
     */
    int row = gridSize;
    int col = gridColSize[0];
    int left[row][col];
    memset(left, 0, sizeof(left));
    int top[row][col];
    memset(top, 0, sizeof(top));

    int i, j;
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j) {
            left[i][j] = grid[i][j] + (j && grid[i][j] ? left[i][j - 1] : 0);
            top[i][j] = grid[i][j] + (i && grid[i][j] ? top[i - 1][j] : 0);
        }
    }

    int min, topMin, leftMin;
    int idx;
    for (idx = fmin(row, col); idx > 0; --idx) {
        for (i = 0; i < row - idx + 1; ++i) {
            for (j = 0; j < col - idx + 1; ++j) {
                topMin = fmin(top[i + idx - 1][j], top[i + idx - 1][j + idx - 1]);
                leftMin = fmin(left[i][j + idx - 1], left[i + idx - 1][j + idx - 1]);
                min = fmin(topMin, leftMin);
                if (min >= idx) {
                    retVal = idx * idx;
                    return retVal;
                }
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}, 3, {3, 3, 3}}, {{{1, 1, 0, 0}}, 1, {4}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
     *  Output: 9
     *
     *  Input: grid = [[1,1,0,0]]
     *  Output: 1
     */

    int** pGrid = NULL;
    int answer = 0;
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
                    if (pGrid[k]) {
                        free(pGrid[k]);
                    }
                }
                free(pGrid);
                pGrid = NULL;
                return EXIT_FAILURE;
            }
            memset(pGrid[j], 0, testCase[i].gridColSize[j] * sizeof(int));
            memcpy(pGrid[j], testCase[i].grid[j], testCase[i].gridColSize[j] * sizeof(int));
        }

        answer = largest1BorderedSquare(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
