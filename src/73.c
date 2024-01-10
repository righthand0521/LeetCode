#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int row[matrixSize];
    memset(row, 0, matrixSize * sizeof(int));
    int column[*matrixColSize];
    memset(column, 0, *matrixColSize * sizeof(int));

    int i, j;
    for (i = 0; i < matrixSize; ++i) {
        for (j = 0; j < *matrixColSize; ++j) {
            if (matrix[i][j] == 0) {
                row[i] = 1;
                column[j] = 1;
            }
        }
    }

    for (i = 0; i < matrixSize; ++i) {
        for (j = 0; j < *matrixColSize; ++j) {
            if ((row[i] == 1) || (column[j] == 1)) {
                matrix[i][j] = 0;
            }
        }
    }
}

int main(int argc, char** argv) {
#define MAX_ROW 200
#define MAX_COLUMN 200
    struct testCaseType {
        int matrix[MAX_ROW][MAX_COLUMN];
        int matrixSize;
        int matrixColSize;
    } testCase[] = {{{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}, 3, 3}, {{{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}}, 3, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pMatrix = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        pMatrix = malloc(testCase[i].matrixSize * sizeof(*pMatrix));
        if (pMatrix == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            pMatrix[j] = malloc(testCase[i].matrixColSize * sizeof(*pMatrix[j]));
            if (pMatrix[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pMatrix[k]);
                }
                free(pMatrix);
                return EXIT_FAILURE;
            }
            memset(pMatrix[j], 0, testCase[i].matrixColSize * sizeof(*pMatrix[j]));
        }
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            for (k = 0; k < testCase[i].matrixColSize; ++k) {
                pMatrix[j][k] = testCase[i].matrix[j][k];
            }
        }
        printf("Input: matrix = \n");
        printf("       [");
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            printf("%s\n         [", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].matrixColSize; ++k) {
                printf("%s%2d", (k == 0 ? "" : ","), pMatrix[j][k]);
            }
            printf("]");
        }
        printf("\n       ]\n");

        setZeroes(pMatrix, testCase[i].matrixSize, &(testCase[i].matrixColSize));
        printf("Output:\n");
        printf("       [");
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            printf("%s\n         [", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].matrixColSize; ++k) {
                printf("%s%2d", (k == 0 ? "" : ","), pMatrix[j][k]);
            }
            printf("]");
        }
        printf("\n       ]\n");

        printf("\n");

        for (j = 0; j < testCase[i].matrixSize; ++j) {
            free(pMatrix[j]);
        }
        free(pMatrix);
        pMatrix = NULL;
    }

    return EXIT_SUCCESS;
}
