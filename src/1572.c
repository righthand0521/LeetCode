#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int diagonalSum(int** mat, int matSize, int* matColSize) {
    int retVal = 0;

    int i;
    for (i = 0; i < matSize; ++i) {
        retVal += mat[i][i];
        retVal += mat[i][matColSize[i] - 1 - i];
    }
    if (matSize % 2 == 1) {
        retVal -= mat[matSize / 2][matSize / 2];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int mat[MAX_SIZE][MAX_SIZE];
        int matSize;
        int matColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 3, {3, 3, 3}},
                    {{{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}}, 4, {4, 4, 4, 4}},
                    {{{5}}, 1, {1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: mat = [[1,2,3],
                      [4,5,6],
                      [7,8,9]]
     *  Output: 25
     *
     *  Input: mat = [[1,1,1,1],
                      [1,1,1,1],
                      [1,1,1,1],
                      [1,1,1,1]]
     *  Output: 8
     *
     *  Input: mat = [[5]]
     *  Output: 5
     */

    int** pMat = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: mat = [");
        for (j = 0; j < testCase[i].matSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",\n              ");
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
        answer = diagonalSum(pMat, testCase[i].matSize, testCase[i].matColSize);
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
