#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** matrixReshape(int** mat, int matSize, int* matColSize, int r, int c, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;
    int i, j;

    if ((matSize * (*matColSize)) != (r * c)) {
        pRetVal = mat;
        (*returnSize) = matSize;
        (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
        if ((*returnColumnSizes) == NULL) {
            perror("malloc");
            return pRetVal;
        }
        for (i = 0; i < (*returnSize); ++i) {
            (*returnColumnSizes)[i] = (*matColSize);
        }

        return pRetVal;
    }

    (*returnSize) = r;
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < (*returnSize); ++i) {
        (*returnColumnSizes)[i] = c;
    }
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    int m = 0;
    int n = 0;
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = (int*)malloc(((*returnColumnSizes)[i]) * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }

        for (j = 0; j < ((*returnColumnSizes)[i]); ++j) {
            pRetVal[i][j] = mat[m][n++];
            if (n == (*matColSize)) {
                ++m;
                n = 0;
            }
            if (m == matSize) {
                return pRetVal;
            }
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int mat[MAX_SIZE][MAX_SIZE];
        int matSize;
        int matColSize[MAX_SIZE];
        int r;
        int c;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 2}, {3, 4}}, 2, {2, 2}, 1, 4, 0, NULL}, {{{1, 2}, {3, 4}}, 2, {2, 2}, 2, 4, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pMat = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: mat =  [");
        for (j = 0; j < testCase[i].matSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].matColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].mat[j][k]);
            }
            printf("]");
        }
        printf("], r = %d, c = %d\n", testCase[i].r, testCase[i].c);

        pMat = (int**)malloc(testCase[i].matSize * sizeof(int*));
        if (pMat == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (k = 0; k < testCase[i].matSize; ++k) {
            pMat[k] = (int*)malloc(testCase[i].matColSize[k] * sizeof(int));
            if (pMat[k] == NULL) {
                perror("malloc");
                for (k = 0; k < testCase[i].matSize; ++k) {
                    if (pMat[k]) {
                        free(pMat[k]);
                    }
                }
                free(pMat);
                pMat = NULL;
                return EXIT_FAILURE;
            }
            memset(pMat[k], 0, testCase[i].matColSize[k] * sizeof(int));
            memcpy(pMat[k], testCase[i].mat[k], testCase[i].matColSize[k] * sizeof(int));
        }
        pAnswer = matrixReshape(pMat, testCase[i].matSize, testCase[i].matColSize, testCase[i].r, testCase[i].c,
                                &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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
        if ((testCase[i].matSize * testCase[i].matColSize[0]) != (testCase[i].r * testCase[i].c)) {
            continue;
        }
        for (k = 0; k < testCase[i].matSize; ++k) {
            if (pMat[k]) {
                free(pMat[k]);
            }
        }
        free(pMat);
        pMat = NULL;
    }

    return EXIT_SUCCESS;
}
