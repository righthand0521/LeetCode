#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int largestSubmatrix(int** matrix, int matrixSize, int* matrixColSize) {
    int retVal = 0;

    int rowSize = matrixSize;
    int colSize = matrixColSize[0];
    int x, y;

    for (x = 1; x < rowSize; ++x) {
        for (y = 0; y < colSize; ++y) {
            if (matrix[x][y] == 1) {
                matrix[x][y] += matrix[x - 1][y];
            }
        }
    }

    for (x = 0; x < rowSize; ++x) {
        qsort(matrix[x], colSize, sizeof(int), compareInteger);
        for (y = 0; y < colSize; ++y) {
            retVal = fmax(retVal, matrix[x][y] * (y + 1));
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (int)(1e2)
#define MAX_COLUMN (int)(1e2)
    struct testCaseType {
        int matrix[MAX_ROW][MAX_COLUMN];
        int matrixSize;
        int matrixColSize[MAX_ROW];
    } testCase[] = {{{{0, 0, 1}, {1, 1, 1}, {1, 0, 1}}, 3, {3, 3, 3}},
                    {{{1, 0, 1, 0, 1}}, 1, {5}},
                    {{{1, 1, 0}, {1, 0, 1}}, 2, {3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
     *  Output: 4
     *
     *  Input: matrix = [[1,0,1,0,1]]
     *  Output: 3
     *
     *  Input: matrix = [[1,1,0],[1,0,1]]
     *  Output: 2
     */

    int** pMatrix = NULL;
    int answer = 0;
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
            memset(pMatrix[j], 0, testCase[i].matrixColSize[j] * sizeof(int));
            memcpy(pMatrix[j], testCase[i].matrix[j], testCase[i].matrixColSize[j] * sizeof(int));
        }
        answer = largestSubmatrix(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize);
        printf("Output: %d\n", answer);

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
