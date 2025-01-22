#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** updateMatrix(int** mat, int matSize, int* matColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    int i, j;

    (*returnColumnSizes) = (int*)calloc(matSize, sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("calloc");
        return pRetVal;
    }
    memcpy((*returnColumnSizes), matColSize, (matSize * sizeof(int)));
    pRetVal = (int**)malloc(matSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (i = 0; i < matSize; ++i) {
        pRetVal[i] = (int*)calloc(matColSize[i], sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("calloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
        }
        (*returnColumnSizes)[i] = matColSize[i];
    }
    (*returnSize) = matSize;

    int maxValue = (int)(1e5);  // 1 <= m, n <= 10^4, 1 <= m * n <= 10^4
    for (i = 0; i < (*returnSize); ++i) {
        for (j = 0; j < ((*returnColumnSizes)[i]); ++j) {
            if (mat[i][j] != 0) {
                pRetVal[i][j] = maxValue;
            }
        }
    }
    for (i = 0; i < (*returnSize); ++i) {
        for (j = 0; j < ((*returnColumnSizes)[i]); ++j) {
            if (i - 1 >= 0) {
                pRetVal[i][j] = fmin(pRetVal[i][j], pRetVal[i - 1][j] + 1);
            }
            if (j - 1 >= 0) {
                pRetVal[i][j] = fmin(pRetVal[i][j], pRetVal[i][j - 1] + 1);
            }
        }
    }
    for (i = (*returnSize) - 1; i >= 0; --i) {
        for (j = ((*returnColumnSizes)[i]) - 1; j >= 0; --j) {
            if (i + 1 < matSize) {
                pRetVal[i][j] = fmin(pRetVal[i][j], pRetVal[i + 1][j] + 1);
            }
            if (j + 1 < ((*returnColumnSizes)[i])) {
                pRetVal[i][j] = fmin(pRetVal[i][j], pRetVal[i][j + 1] + 1);
            }
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e3)
    struct testCaseType {
        int mat[MAX_SIZE][MAX_SIZE];
        int matSize;
        int matColSize[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}, 3, {3, 3, 3}, 0, NULL},
                    {{{0, 0, 0}, {0, 1, 0}, {1, 1, 1}}, 3, {3, 3, 3}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
     *  Output: [[0,0,0],[0,1,0],[0,0,0]]
     *
     *  Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
     *  Output: [[0,0,0],[0,1,0],[1,2,1]]
     */

    int** pMat = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: mat =  [");
        for (j = 0; j < testCase[i].matSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].matColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].mat[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pMat = (int**)malloc(testCase[i].matSize * sizeof(int*));
        if (pMat == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].matSize; ++j) {
            pMat[j] = (int*)malloc(testCase[i].matColSize[j] * sizeof(int));
            if (pMat[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pMat[k]) {
                        free(pMat[k]);
                        pMat[k] = NULL;
                    }
                }
                free(pMat);
                pMat = NULL;
                return EXIT_FAILURE;
            }
            memset(pMat[j], 0, testCase[i].matColSize[j] * sizeof(int));
            memcpy(pMat[j], testCase[i].mat[j], testCase[i].matColSize[j] * sizeof(int));
        }
        pAnswer = updateMatrix(pMat, testCase[i].matSize, testCase[i].matColSize, &testCase[i].returnSize,
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

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;

        for (j = 0; j < testCase[i].matSize; ++j) {
            if (pMat[j]) {
                free(pMat[j]);
                pMat[j] = NULL;
            }
        }
        free(pMat);
        pMat = NULL;
    }

    return EXIT_SUCCESS;
}
