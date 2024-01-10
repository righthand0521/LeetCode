#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isToeplitzMatrix(int** matrix, int matrixSize, int* matrixColSize) {
    bool retVal = false;

    int i, j;
    for (i = 1; i < matrixSize; ++i) {
        for (j = 1; j < matrixColSize[i]; ++j) {
            if (matrix[i - 1][j - 1] != matrix[i][j]) {
                return retVal;
            }
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        int matrix[MAX_SIZE][MAX_SIZE];
        int matrixSize;
        int matrixColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2, 3, 4}, {5, 1, 2, 3}, {9, 5, 1, 2}}, 3, {4, 4, 4}}, {{{1, 2}, {2, 2}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pMatrix = NULL;
    bool answer = false;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: matrix = [");
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
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
                    if (pMatrix[k]) {
                        free(pMatrix[k]);
                        pMatrix[k] = NULL;
                    }
                }
                free(pMatrix);
                pMatrix = NULL;
                return EXIT_FAILURE;
            }
            memset(pMatrix[j], 0, testCase[i].matrixColSize[j] * sizeof(int));
            memcpy(pMatrix[j], testCase[i].matrix[j], testCase[i].matrixColSize[j] * sizeof(int));
        }
        answer = isToeplitzMatrix(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize);

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
