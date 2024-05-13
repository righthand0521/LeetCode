#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matrixScore(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    // Set score to summation of first column
    retVal = (1 << (gridColSize[0] - 1)) * gridSize;

    int countSameBits, columnScore;
    int row, col;
    for (col = 1; col < gridColSize[0]; col++) {
        countSameBits = 0;
        for (row = 0; row < gridSize; row++) {
            // Count elements matching first in row
            if (grid[row][col] == grid[row][0]) {
                countSameBits++;
            }
        }

        // Calculate score based on the number of same bits in a column
        countSameBits = fmax(countSameBits, gridSize - countSameBits);

        // Calculate the score contribution for the current column
        columnScore = (1 << (gridColSize[0] - col - 1)) * countSameBits;

        // Add contribution to score
        retVal += columnScore;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{0, 0, 1, 1}, {1, 0, 1, 0}, {1, 1, 0, 0}}, 3, {4, 4, 4}}, {{{0}}, 1, {1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
     *  Output: 39
     *
     *  Input: grid = [[0]]
     *  Output: 1
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
        answer = matrixScore(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
