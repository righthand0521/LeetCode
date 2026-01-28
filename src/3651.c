#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int** gridPtr = NULL;
int compareIntArray(const void* a, const void* b) {
    int retVal = 0;

    int* pa = (int*)a;
    int* pb = (int*)b;
    retVal = gridPtr[pa[0]][pa[1]] - gridPtr[pb[0]][pb[1]];

    return retVal;
}
int minCost(int** grid, int gridSize, int* gridColSize, int k) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    gridPtr = grid;
    int points[rowSize * colSize][2], idx = 0;
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            points[idx][0] = i;
            points[idx++][1] = j;
        }
    }
    qsort(points, rowSize * colSize, sizeof(points[0]), compareIntArray);

    int costs[rowSize][colSize];
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            costs[i][j] = INT_MAX;
        }
    }

    int minCost, x, y;
    for (int t = 0; t <= k; t++) {
        minCost = INT_MAX;
        for (int i = 0, j = 0; i < rowSize * colSize; i++) {
            x = points[i][0];
            y = points[i][1];
            minCost = fmin(minCost, costs[x][y]);

            if ((i + 1 < rowSize * colSize) && (grid[x][y] == grid[points[i + 1][0]][points[i + 1][1]])) {
                continue;
            }

            for (int r = j; r <= i; r++) {
                costs[points[r][0]][points[r][1]] = minCost;
            }

            j = i + 1;
        }

        for (int i = rowSize - 1; i >= 0; i--) {
            for (int j = colSize - 1; j >= 0; j--) {
                if ((i == rowSize - 1) && (j == colSize - 1)) {
                    costs[i][j] = 0;
                    continue;
                }

                if (i != rowSize - 1) {
                    costs[i][j] = fmin(costs[i][j], costs[i + 1][j] + grid[i + 1][j]);
                }

                if (j != colSize - 1) {
                    costs[i][j] = fmin(costs[i][j], costs[i][j + 1] + grid[i][j + 1]);
                }
            }
        }
    }
    retVal = costs[0][0];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (80)
#define MAX_COLUMN (80)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
        int k;
    } testCase[] = {{{{1, 3, 3}, {2, 5, 4}, {4, 3, 5}}, 3, {3, 3, 3}, 2}, {{{1, 2}, {2, 3}, {3, 4}}, 3, {2, 2, 2}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,3,3],[2,5,4],[4,3,5]], k = 2
     *  Output: 7
     *
     *  Input: grid = [[1,2],[2,3],[3,4]], k = 1
     *  Output: 9
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
        printf("], k = %d\n", testCase[i].k);

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
        answer = minCost(pGrid, testCase[i].gridSize, testCase[i].gridColSize, testCase[i].k);
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
