#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMissingAndRepeatedValues(int** grid, int gridSize, int* gridColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)calloc(2, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    // Store frequency of each number in the grid
    int freqSize = gridSize * gridSize + 1;  // 1 <= grid[i][j] <= n * n
    int freq[freqSize];
    memset(freq, 0, sizeof(freq));
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridColSize[i]; ++j) {
            freq[grid[i][j]]++;
        }
    }

    // Check numbers from 1 to n^2 to find missing and repeated values
    for (int num = 1; num <= gridSize * gridSize; num++) {
        if (freq[num] == 0) {
            pRetVal[1] = num;
        } else if (freq[num] == 2) {
            pRetVal[0] = num;
        }
    }
    (*returnSize) = 2;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{{{1, 3}, {2, 2}}, 2, {2, 2}, 0}, {{{9, 1, 7}, {8, 9, 2}, {3, 4, 6}}, 3, {3, 3, 3}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,3],[2,2]]
     *  Output: [2,4]
     *
     *  Input: grid = [[9,1,7],[8,9,2],[3,4,6]]
     *  Output: [9,5]
     */

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
        pAnswer =
            findMissingAndRepeatedValues(pGrid, testCase[i].gridSize, testCase[i].gridColSize, &testCase[i].returnSize);
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
