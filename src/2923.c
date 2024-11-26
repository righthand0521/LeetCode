#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findChampion(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int stronger = 0;
    int x, y;
    for (x = 0; x < gridSize; ++x) {
        stronger = 0;
        for (y = 0; y < gridColSize[x]; ++y) {
            stronger += grid[x][y];
        }

        if (stronger == gridSize - 1) {
            retVal = x;
            break;
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
    } testCase[] = {{{{0, 1}, {0, 0}}, 2, {2, 2}}, {{{0, 0, 1}, {1, 0, 1}, {0, 0, 0}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,1],[0,0]]
     *  Output: 0
     *
     *  Input: grid = [[0,0,1],[1,0,1],[0,0,0]]
     *  Output: 1
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
        answer = findChampion(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
