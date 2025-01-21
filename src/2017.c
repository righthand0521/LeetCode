#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long gridGame(int** grid, int gridSize, int* gridColSize) {
    long long retVal = 0;

    long long firstRowSum = 0;
    for (int i = 0; i < gridColSize[0]; ++i) {
        firstRowSum += grid[0][i];
    }
    long long secondRowSum = 0;
    long long minimumSum = LLONG_MAX;
    for (int turnIndex = 0; turnIndex < gridColSize[0]; ++turnIndex) {
        firstRowSum -= grid[0][turnIndex];
        minimumSum = fmin(minimumSum, fmax(firstRowSum, secondRowSum));
        secondRowSum += grid[1][turnIndex];
    }
    retVal = minimumSum;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(5 * 100)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{2, 5, 4}, {1, 5, 1}}, 2, {3, 3}},
                    {{{3, 3, 1}, {8, 5, 2}}, 2, {3, 3}},
                    {{{1, 3, 1, 15}, {1, 3, 3, 1}}, 2, {4, 4}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[2,5,4],[1,5,1]]
     *  Output: 4
     *
     *  Input: grid = [[3,3,1],[8,5,2]]
     *  Output: 4
     *
     *  Input: grid = [[1,3,1,15],[1,3,3,1]]
     *  Output: 7
     */

    int** pGrid = NULL;
    long long answer;
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
        answer = gridGame(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
        printf("Output: %lld\n", answer);

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
