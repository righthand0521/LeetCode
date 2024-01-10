#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numSpecial(int** mat, int matSize, int* matColSize) {
    int retVal = 0;

    // m == mat.length, n == mat[i].length, 1 <= m, n <= 100.
    int rowSize = matSize;
    int colSize = matColSize[0];

    int rowSum[rowSize];
    memset(rowSum, 0, sizeof(rowSum));
    int colSum[colSize];
    memset(colSum, 0, sizeof(colSum));

    int i, j;
    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            // mat[i][j] is either 0 or 1.
            rowSum[i] += mat[i][j];
            colSum[j] += mat[i][j];
        }
    }

    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            if (mat[i][j] != 1) {
                continue;
            }
            if ((rowSum[i] == 1) && (colSum[j] == 1)) {
                retVal += 1;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int mat[MAX_SIZE][MAX_SIZE];
        int matSize;
        int matColSize[MAX_SIZE];
    } testCase[] = {{{{1, 0, 0}, {0, 0, 1}, {1, 0, 0}}, 3, {3, 3, 3}},
                    {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
     *  Output: 1
     *
     *  Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
     *  Output: 3
     */

    int** pMat = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: mat = [");
        for (j = 0; j < testCase[i].matSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
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
        answer = numSpecial(pMat, testCase[i].matSize, testCase[i].matColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (k = 0; k < testCase[i].matSize; ++k) {
            if (pMat[k]) {
                free(pMat[k]);
                pMat[k] = NULL;
            }
        }
        free(pMat);
        pMat = NULL;
    }

    return EXIT_SUCCESS;
}
