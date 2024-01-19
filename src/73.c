#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int matrixRow = matrixSize;
    int matrixCol = matrixColSize[0];

    int rowHashTable[matrixRow];
    memset(rowHashTable, 0, matrixRow * sizeof(int));
    int colHashTable[matrixCol];
    memset(colHashTable, 0, matrixCol * sizeof(int));

    int i, j;
    for (i = 0; i < matrixRow; ++i) {
        for (j = 0; j < matrixCol; ++j) {
            if (matrix[i][j] == 0) {
                rowHashTable[i] = 1;
                colHashTable[j] = 1;
            }
        }
    }

    for (i = 0; i < matrixRow; ++i) {
        for (j = 0; j < matrixCol; ++j) {
            if ((rowHashTable[i] == 1) || (colHashTable[j] == 1)) {
                matrix[i][j] = 0;
            }
        }
    }
}

int main(int argc, char** argv) {
#define MAX_ROW (200)
#define MAX_COLUMN (200)
    struct testCaseType {
        int matrix[MAX_ROW][MAX_COLUMN];
        int matrixSize;
        int matrixColSize[MAX_ROW];
    } testCase[] = {{{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}, 3, {3, 3, 3}},
                    {{{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}}, 3, {4, 4, 4}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
     *  Output: [[1,0,1],[0,0,0],[1,0,1]]
     *
     *  Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
     *  Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
     */

    int** pMatrix = NULL;
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
                    free(pMatrix[k]);
                    pMatrix[k] = NULL;
                }
                free(pMatrix);
                pMatrix = NULL;
                return EXIT_FAILURE;
            }
            memset(pMatrix[j], 0, (testCase[i].matrixColSize[j] * sizeof(int)));
            memcpy(pMatrix[j], testCase[i].matrix[j], (testCase[i].matrixColSize[j] * sizeof(int)));
        }
        setZeroes(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].matrixColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pMatrix[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].matrixSize; ++j) {
            free(pMatrix[j]);
            pMatrix[j] = NULL;
        }
        free(pMatrix);
        pMatrix = NULL;
    }

    return EXIT_SUCCESS;
}
