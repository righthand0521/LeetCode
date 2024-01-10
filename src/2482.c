#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** onesMinusZeros(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    // m == grid.length, n == grid[i].length, 1 <= m, n <= 10^5.
    int rowSize = gridSize;
    int colSize = gridColSize[0];
    int i, j;

    pRetVal = (int**)malloc(rowSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < rowSize; ++i) {
        pRetVal[i] = (int*)malloc(colSize * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[i], 0, (colSize * sizeof(int)));
    }

    (*returnColumnSizes) = (int*)malloc(rowSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        for (j = 0; j < rowSize; ++j) {
            free(pRetVal[j]);
            pRetVal[j] = NULL;
        }
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (rowSize * sizeof(int)));

    int rowSum[rowSize];
    memset(rowSum, 0, sizeof(rowSum));
    int colSum[colSize];
    memset(colSum, 0, sizeof(colSum));
    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            // grid[i][j] is either 0 or 1.
            rowSum[i] += grid[i][j];
            colSum[j] += grid[i][j];
        }
    }

    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            pRetVal[i][j] = rowSum[i] + colSum[j];
            pRetVal[i][j] -= (rowSize - rowSum[i]);
            pRetVal[i][j] -= (colSize - colSum[j]);
        }
        (*returnColumnSizes)[i] = colSize;
    }
    (*returnSize) = rowSize;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{0, 1, 1}, {1, 0, 1}, {0, 0, 1}}, 3, {3, 3, 3}, 0, NULL},
                    {{{1, 1, 1}, {1, 1, 1}}, 2, {3, 3}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,1,1],[1,0,1],[0,0,1]]
     *  Output: [[0,0,4],[0,0,4],[-2,-2,2]]
     *
     *  Input: grid = [[1,1,1],[1,1,1]]
     *  Output: [[5,5,5],[5,5,5]]
     */

    int** pGrid = NULL;
    int** pAnswer;
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
                    if (pGrid[k]) {
                        free(pGrid[k]);
                        pGrid[k] = NULL;
                    }
                }
                free(pGrid);
                pGrid = NULL;
                return EXIT_FAILURE;
            }
            memset(pGrid[j], 0, testCase[i].gridColSize[j] * sizeof(int));
            memcpy(pGrid[j], testCase[i].grid[j], testCase[i].gridColSize[j] * sizeof(int));
        }
        pAnswer = onesMinusZeros(pGrid, testCase[i].gridSize, testCase[i].gridColSize, &testCase[i].returnSize,
                                 &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        for (k = 0; k < testCase[i].returnSize; ++k) {
            if (pAnswer[k]) {
                free(pAnswer[k]);
                pAnswer[k] = NULL;
            }
        }
        free(pAnswer);
        pAnswer = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (k = 0; k < testCase[i].gridSize; ++k) {
            if (pGrid[k]) {
                free(pGrid[k]);
                pGrid[k] = NULL;
            }
        }
        free(pGrid);
        pGrid = NULL;
    }

    return EXIT_SUCCESS;
}
