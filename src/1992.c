#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findFarmland(int** land, int landSize, int* landColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    int mallocSize = landSize * landColSize[0];
    pRetVal = (int**)malloc(mallocSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int*)malloc(mallocSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        goto exit1;
    }
    memset((*returnColumnSizes), 0, (landSize * sizeof(int)));

    int x, y;
    int row, col;
    for (row = 0; row < landSize; ++row) {
        for (col = 0; col < landColSize[row]; ++col) {
            if (land[row][col] == 0) {
                continue;
            }

            x = row;
            y = col;
            for (x = row; x < landSize; ++x) {
                if (land[x][col] == 0) {
                    break;
                }

                for (y = col; y < landColSize[row]; ++y) {
                    if (land[x][y] == 0) {
                        break;
                    }
                    land[x][y] = 0;
                }
            }

            (*returnColumnSizes)[(*returnSize)] = 4;
            pRetVal[(*returnSize)] = (int*)malloc((*returnColumnSizes)[(*returnSize)] * sizeof(int));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                goto exit2;
            }
            pRetVal[(*returnSize)][0] = row;
            pRetVal[(*returnSize)][1] = col;
            pRetVal[(*returnSize)][2] = x - 1;
            pRetVal[(*returnSize)][3] = y - 1;
            (*returnSize) += 1;
        }
    }

    return pRetVal;

exit2:
    free((*returnColumnSizes));
    (*returnColumnSizes) = NULL;

    int i;
    for (i = 0; i < (*returnSize); ++i) {
        free(pRetVal[i]);
        pRetVal[i] = NULL;
    }

exit1:
    free(pRetVal);
    pRetVal = NULL;
    (*returnSize) = 0;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (300)
#define MAX_COL (300)
    struct testCaseType {
        int land[MAX_ROW][MAX_COL];
        int landSize;
        int landColSize[MAX_ROW];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 0, 0}, {0, 1, 1}, {0, 1, 1}}, 3, {3, 3, 3}, 0, NULL},
                    {{{1, 1}, {1, 1}}, 2, {2, 2}, 0, NULL},
                    {{{0}}, 1, {1}, 0, NULL},
                    {{{1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1}}, 1, {13}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: land = [[1,0,0],[0,1,1],[0,1,1]]
     *  Output: [[0,0,0,0],[1,1,2,2]]
     *
     *  Input: land = [[1,1],[1,1]]
     *  Output: [[0,0,1,1]]
     *
     *  Input: land = [[0]]
     *  Output: []
     *
     *  Input: land = [[1,0,0,1,0,1,1,0,0,1,0,1,1]]
     *  Output: [[0,0,0,0],[0,3,0,3],[0,5,0,6],[0,9,0,9],[0,11,0,12]]
     */

    int** pLand = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: land = [");
        for (j = 0; j < testCase[i].landSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].landColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].land[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pLand = (int**)malloc(testCase[i].landSize * sizeof(int*));
        if (pLand == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].landSize; ++j) {
            pLand[j] = (int*)malloc(testCase[i].landColSize[j] * sizeof(int));
            if (pLand[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pLand[k]);
                }
                free(pLand);
                return EXIT_FAILURE;
            }
            memset(pLand[j], 0, (testCase[i].landColSize[j] * sizeof(int)));
            memcpy(pLand[j], testCase[i].land[j], (testCase[i].landColSize[j] * sizeof(int)));
        }

        pAnswer = findFarmland(pLand, testCase[i].landSize, testCase[i].landColSize, &testCase[i].returnSize,
                               &(testCase[i].returnColumnSizes));
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].landSize; ++j) {
            free(pLand[j]);
            pLand[j] = NULL;
        }
        free(pLand);
        pLand = NULL;
    }

    return EXIT_SUCCESS;
}
