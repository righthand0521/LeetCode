#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkValid(int** matrix, int matrixSize, int* matrixColSize) {
    bool retVal = false;

#define MAX_SIZE (matrixSize)
    int HASHTABLE[MAX_SIZE];
    int idx;

    int i, j;

    // check every row
    for (i = 0; i < matrixSize; ++i) {
        memset(HASHTABLE, 0, sizeof(HASHTABLE));
        for (j = 0; j < matrixColSize[i]; ++j) {
            idx = matrix[i][j] - 1;
            if (HASHTABLE[idx] != 0) {
                return retVal;
            }
            ++HASHTABLE[idx];
        }
    }

    // check every column
    for (j = 0; j < matrixColSize[0]; ++j) {
        memset(HASHTABLE, 0, sizeof(HASHTABLE));
        for (i = 0; i < matrixSize; ++i) {
            idx = matrix[i][j] - 1;
            if (HASHTABLE[idx] != 0) {
                return retVal;
            }
            ++HASHTABLE[idx];
        }
    }

    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MATRIX_SIZE (100)
    struct testCaseType {
        int matrix[MATRIX_SIZE][MATRIX_SIZE];
        int matrixSize;
        int matrixColSize[MATRIX_SIZE];
    } testCase[] = {{{{1, 2, 3}, {3, 1, 2}, {2, 3, 1}}, 3, {3, 3, 3}},
                    {{{1, 1, 1}, {1, 2, 3}, {1, 2, 3}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pMatrix = NULL;
    bool answer = false;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: matrix = \n[");
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            printf("%s[", (j == 0) ? "" : "\n,");
            for (k = 0; k < testCase[i].matrixColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].matrix[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pMatrix = (int**)malloc(testCase[i].matrixSize * sizeof(int*));
        if (pMatrix == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            pMatrix[j] = (int*)malloc(testCase[i].matrixColSize[j] * sizeof(int));
            if (pMatrix[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pMatrix[k]);
                    pMatrix[k] = NULL;
                }
                free(pMatrix);
                pMatrix = NULL;
                return EXIT_FAILURE;
            }
            memset(pMatrix[j], 0, testCase[i].matrixColSize[j] * sizeof(int));
            memcpy(pMatrix[j], testCase[i].matrix[j], testCase[i].matrixColSize[j] * sizeof(int));
        }
        answer = checkValid(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");

        for (j = 0; j < testCase[i].matrixSize; ++j) {
            if (pMatrix[j]) {
                free(pMatrix[j]);
                pMatrix[j] = NULL;
            }
        }
        free(pMatrix);
        pMatrix = NULL;
    }

    return EXIT_SUCCESS;
}
