#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int direction[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
int backtrack(int** grid, int gridSize, int gridColSize, int row, int col) {
    int retVal = 0;

    // Base case: this cell is not in the matrix or has no gold
    if ((row < 0) || (col < 0) || (row == gridSize) || (col == gridColSize) || (grid[row][col] == 0)) {
        return retVal;
    }

    // Mark the cell as visited and save the value
    int originalVal = grid[row][col];
    grid[row][col] = 0;

    // Backtrack in each of the four directions
    int i;
    for (i = 0; i < 4; ++i) {
        retVal = fmax(retVal, backtrack(grid, gridSize, gridColSize, row + direction[i][0], col + direction[i][1]));
    }

    // Set the cell back to its original value
    grid[row][col] = originalVal;

    retVal += originalVal;

    return retVal;
}
int getMaximumGold(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    // Search for the path with the maximum gold starting from each cell
    int row, col;
    for (row = 0; row < gridSize; ++row) {
        for (col = 0; col < gridColSize[0]; ++col) {
            retVal = fmax(retVal, backtrack(grid, gridSize, gridColSize[0], row, col));
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (15)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{0, 6, 0}, {5, 8, 7}, {0, 9, 0}}, 3, {3, 3, 3}},
                    {{{1, 0, 7}, {2, 0, 6}, {3, 4, 5}, {0, 3, 0}, {9, 0, 20}}, 5, {3, 3, 3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
     *  Output: 24
     *
     *  Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
     *  Output: 28
     */

    int** pGrid = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", "[");
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
            memset(pGrid[j], 0, (testCase[i].gridColSize[j] * sizeof(int)));
            memcpy(pGrid[j], testCase[i].grid[j], (testCase[i].gridColSize[j] * sizeof(int)));
        }
        answer = getMaximumGold(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
