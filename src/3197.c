#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumSum2(int** grid, int gridSize, int* gridColSize, int u, int d, int l, int r) {
    int min_i = gridSize, max_i = 0;
    int min_j = gridColSize[0], max_j = 0;
    for (int i = u; i <= d; i++) {
        for (int j = l; j <= r; j++) {
            if (grid[i][j] == 1) {
                min_i = fmin(min_i, i);
                min_j = fmin(min_j, j);
                max_i = fmax(max_i, i);
                max_j = fmax(max_j, j);
            }
        }
    }
    return min_i <= max_i ? (max_i - min_i + 1) * (max_j - min_j + 1) : INT_MAX / 3;
}
int solve(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];
    int x, y, z;
    retVal = rowSize * colSize;
    for (int i = 0; i + 1 < rowSize; i++) {
        for (int j = 0; j + 1 < colSize; j++) {
            x = minimumSum2(grid, rowSize, gridColSize, 0, i, 0, colSize - 1);
            y = minimumSum2(grid, rowSize, gridColSize, i + 1, rowSize - 1, 0, j);
            z = minimumSum2(grid, rowSize, gridColSize, i + 1, rowSize - 1, j + 1, colSize - 1);
            retVal = fmin(retVal, x + y + z);

            x = minimumSum2(grid, rowSize, gridColSize, 0, i, 0, j);
            y = minimumSum2(grid, rowSize, gridColSize, 0, i, j + 1, colSize - 1);
            z = minimumSum2(grid, rowSize, gridColSize, i + 1, rowSize - 1, 0, colSize - 1);
            retVal = fmin(retVal, x + y + z);
        }
    }
    for (int i = 0; i + 2 < rowSize; i++) {
        for (int j = i + 1; j + 1 < rowSize; j++) {
            x = minimumSum2(grid, rowSize, gridColSize, 0, i, 0, colSize - 1);
            y = minimumSum2(grid, rowSize, gridColSize, i + 1, j, 0, colSize - 1);
            z = minimumSum2(grid, rowSize, gridColSize, j + 1, rowSize - 1, 0, colSize - 1);
            retVal = fmin(retVal, x + y + z);
        }
    }

    return retVal;
}
int** rotate(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColSizes) {
    int** pRetVal = NULL;

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    (*returnSize) = 0;
    (*returnColSizes) = (int*)malloc(colSize * sizeof(int));
    if ((*returnColSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal = (int**)malloc(colSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColSizes));
        (*returnColSizes) = NULL;
        return pRetVal;
    }
    for (int i = 0; i < colSize; i++) {
        pRetVal[i] = (int*)malloc(rowSize * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; j++) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free((*returnColSizes));
            (*returnColSizes) = NULL;
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        (*returnColSizes)[i] = rowSize;
    }

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            pRetVal[colSize - j - 1][i] = grid[i][j];
        }
    }
    (*returnSize) = colSize;

    return pRetVal;
}
int minimumSum(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rotateGridSize = 0;
    int* rotateGridColSizes = NULL;
    int** rotateGrid = rotate(grid, gridSize, gridColSize, &rotateGridSize, &rotateGridColSizes);
    if (rotateGrid != NULL) {
        retVal = fmin(solve(grid, gridSize, gridColSize), solve(rotateGrid, rotateGridSize, rotateGridColSizes));
    }

    //
    for (int i = 0; i < rotateGridSize; i++) {
        free(rotateGrid[i]);
        rotateGrid[i] = NULL;
    }
    free(rotateGrid);
    rotateGrid = NULL;
    free(rotateGridColSizes);
    rotateGridColSizes = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (30)
#define MAX_COLUMN (30)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {{{{1, 0, 1}, {1, 1, 1}}, 2, {3, 3}}, {{{1, 0, 1, 0}, {0, 1, 0, 1}}, 2, {4, 4}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,0,1],[1,1,1]]
     *  Output: 5
     *
     *  Input: grid = [[1,0,1,0],[0,1,0,1]]
     *  Output: 5
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
        answer = minimumSum(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
