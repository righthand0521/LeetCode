#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUCK (-1)
bool isOutBound(int gridRowSize, int gridColumnSize, int row, int column) {
    if ((row >= gridRowSize) || (row < 0)) {
        return false;
    } else if ((column >= gridColumnSize) || (column < 0)) {
        return false;
    }

    return true;
}
int dfs(int** grid, int gridRowSize, int gridColumnSize, int row, int column) {
    // at the bottom
    if (row == gridRowSize) {
        return column;
    }

    // check outbound or not
    if (isOutBound(gridRowSize, gridColumnSize, row, column) == false) {
        return STUCK;
    }

    if (grid[row][column] == 1) {  // redirects the ball to the right spans
        if (isOutBound(gridRowSize, gridColumnSize, row, (column + 1)) == false) {
            return STUCK;
        } else if (grid[row][(column + 1)] != 1) {
            return STUCK;
        }

        return dfs(grid, gridRowSize, gridColumnSize, (row + 1), (column + 1));
    } else if (grid[row][column] == -1) {  // redirects the ball to the left spans
        if (isOutBound(gridRowSize, gridColumnSize, row, (column - 1)) == false) {
            return STUCK;
        } else if (grid[row][(column - 1)] != -1) {
            return STUCK;
        }

        return dfs(grid, gridRowSize, gridColumnSize, (row + 1), (column - 1));
    }

    return STUCK;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findBall(int** grid, int gridSize, int* gridColSize, int* returnSize) {
    int* pRetVal = NULL;
    (*returnSize) = gridColSize[0];

    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, STUCK, (*returnSize) * sizeof(int));

    // only 1 column
    if ((*returnSize) == 1) {
        return pRetVal;
    }

    // Depth-First Search by Recursive
    int i;
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = dfs(grid, gridSize, (*returnSize), 0, i);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{{{1, 1, 1, -1, -1}, {1, 1, 1, -1, -1}, {-1, -1, -1, 1, 1}, {1, 1, 1, 1, -1}, {-1, -1, -1, -1, -1}},
                     5,
                     {5, 5, 5, 5, 5},
                     0},
                    {{{-1}}, 1, {1}, 0},
                    {{{1, 1, 1, 1, 1, 1}, {-1, -1, -1, -1, -1, -1}, {1, 1, 1, 1, 1, 1}, {-1, -1, -1, -1, -1, -1}},
                     4,
                     {6, 6, 6, 6},
                     0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pGrid = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("[");
            for (k = 0; k < testCase[i].gridColSize[j]; ++k) {
                printf("%d%s", testCase[i].grid[j][k], (k == (testCase[i].gridColSize[j] - 1) ? "" : ","));
            }
            printf("%s", (j == (testCase[i].gridSize - 1) ? "]" : "],"));
        }
        printf("\n");

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
        }
        for (j = 0; j < testCase[i].gridSize; ++j) {
            for (k = 0; k < testCase[i].gridColSize[j]; ++k) {
                pGrid[j][k] = testCase[i].grid[j][k];
            }
        }
        pAnswer = findBall(pGrid, testCase[i].gridSize, testCase[i].gridColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].gridSize; ++j) {
            free(pGrid[j]);
        }
        free(pGrid);
        pGrid = NULL;

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
