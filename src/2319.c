#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkXMatrix(int** grid, int gridSize, int* gridColSize) {
    bool retVal = false;

    int i, j;
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridColSize[i]; ++j) {
            if ((j == i) || (j == gridColSize[i] - 1 - i)) {
                if (grid[i][j] == 0) {
                    return retVal;
                }
            } else {
                if (grid[i][j] != 0) {
                    return retVal;
                }
            }
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{2, 0, 0, 1}, {0, 3, 1, 0}, {0, 5, 2, 0}, {4, 0, 0, 2}}, 4, {4, 4, 4, 4}},
                    {{{5, 7, 0}, {0, 3, 1}, {0, 5, 0}}, 3, {3, 3, 3}},
                    {{{5, 0, 0, 1}, {0, 4, 1, 5}, {0, 5, 2, 0}, {4, 1, 0, 2}}, 4, {4, 4, 4, 4}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pGrid = NULL;
    bool answer = false;
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
        answer = checkXMatrix(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
        printf("Output: %s\n", ((answer == true) ? "true" : "false"));

        printf("\n");

        for (j = 0; j < testCase[i].gridSize; ++j) {
            free(pGrid[j]);
        }
        free(pGrid);
        pGrid = NULL;
    }

    return EXIT_SUCCESS;
}
