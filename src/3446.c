#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntegerAscending(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int compareIntegerDescending(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** sortMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    (*returnColumnSizes) = (int*)calloc(gridSize, sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("calloc");
        return pRetVal;
    }
    pRetVal = (int**)malloc(gridSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (int i = 0; i < gridSize; ++i) {
        pRetVal[i] = (int*)calloc(gridColSize[i], sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("calloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (int j = 0; j < i; ++j) {
                free(pRetVal[j]);
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        for (int j = 0; j < gridColSize[i]; j++) {
            pRetVal[i][j] = grid[i][j];
        }
        (*returnColumnSizes)[i] = gridColSize[i];
    }
    (*returnSize) = gridSize;

    int tmp[gridSize + 1];
    int len;

    for (int i = 0; i < gridSize; i++) {
        memset(tmp, 0, sizeof(tmp));
        len = 0;
        for (int j = 0; i + j < gridSize; j++) {
            tmp[len++] = pRetVal[i + j][j];
        }
        qsort(tmp, len, sizeof(int), compareIntegerDescending);

        for (int j = 0; i + j < gridSize; j++) {
            pRetVal[i + j][j] = tmp[j];
        }
    }

    for (int j = 1; j < gridSize; j++) {
        memset(tmp, 0, sizeof(tmp));
        len = 0;
        for (int i = 0; j + i < gridColSize[i]; i++) {
            tmp[len++] = pRetVal[i][j + i];
        }
        qsort(tmp, len, sizeof(int), compareIntegerAscending);

        for (int i = 0; j + i < gridColSize[i]; i++) {
            pRetVal[i][j + i] = tmp[i];
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 7, 3}, {9, 8, 2}, {4, 5, 6}}, 3, {3, 3, 3}, 0, NULL},
                    {{{0, 1}, {1, 2}}, 2, {2, 2}, 0, NULL},
                    {{{1}}, 1, {1}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,7,3],[9,8,2],[4,5,6]]
     *  Output: [[8,2,3],[9,6,7],[4,5,1]]
     *
     *  Input: grid = [[0,1],[1,2]]
     *  Output: [[2,1],[1,0]]
     *
     *  Input: grid = [[1]]
     *  Output: [[1]]
     */

    int** pGrid = NULL;
    int** pAnswer = NULL;
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
                    if (pGrid[k]) {
                        free(pGrid[k]);
                    }
                }
                free(pGrid);
                pGrid = NULL;
                return EXIT_FAILURE;
            }
            memset(pGrid[j], 0, testCase[i].gridColSize[j] * sizeof(int));
            memcpy(pGrid[j], testCase[i].grid[j], testCase[i].gridColSize[j] * sizeof(int));
        }
        pAnswer = sortMatrix(pGrid, testCase[i].gridSize, testCase[i].gridColSize, &testCase[i].returnSize,
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

        for (j = 0; j < testCase[i].gridSize; ++j) {
            if (pGrid[j]) {
                free(pGrid[j]);
                pGrid[j] = NULL;
            }
        }
        free(pGrid);
        pGrid = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
    }

    return EXIT_SUCCESS;
}
