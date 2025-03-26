#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minOperations(int** grid, int gridSize, int* gridColSize, int x) {
    int retVal = 0;

    // Flatten the grid into numsArray
    int numsArraySize = gridSize * gridColSize[0];
    int* numsArray = (int*)malloc(numsArraySize * sizeof(int));
    if (numsArray == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridColSize[row]; col++) {
            numsArray[row * gridColSize[row] + col] = grid[row][col];
        }
    }

    // Sort numsArray in non-decreasing order to easily find the median
    qsort(numsArray, numsArraySize, sizeof(int), compareInteger);

    // Store the median element as the final common value
    int finalCommonNumber = numsArray[numsArraySize / 2];

    for (int i = 0; i < numsArraySize; i++) {
        // If the remainder when divided by x is different for any number, return -1
        if (numsArray[i] % x != finalCommonNumber % x) {
            retVal = -1;
            break;
        }
        // Add the number of operations required to make the current number equal to finalCommonNumber
        retVal += abs(finalCommonNumber - numsArray[i]) / x;
    }

    //
    free(numsArray);
    numsArray = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (int)(1e2)
#define MAX_COLUMN (int)(1e2)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
        int x;
    } testCase[] = {
        {{{2, 4}, {6, 8}}, 2, {2, 2}, 2}, {{{1, 5}, {2, 3}}, 2, {2, 2}, 1}, {{{1, 2}, {3, 4}}, 2, {2, 2}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[2,4],[6,8]], x = 2
     *  Output: 4
     *
     *  Input: grid = [[1,5],[2,3]], x = 1
     *  Output: 5
     *
     *  Input: grid = [[1,2],[3,4]], x = 2
     *  Output: -1
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
        printf("], x = %d\n", testCase[i].x);

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
        answer = minOperations(pGrid, testCase[i].gridSize, testCase[i].gridColSize, testCase[i].x);
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
