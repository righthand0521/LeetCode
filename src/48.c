#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* pNum1, int* pNum2) {
    int temp = *pNum1;
    *pNum1 = *pNum2;
    *pNum2 = temp;
}
void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    int matrixRow = matrixSize;
    int matrixCol = matrixColSize[0];
    int i, j;

    for (i = 0; i < matrixRow; ++i) {
        for (j = 0; j < (matrixCol / 2); ++j) {
            swap(&matrix[i][j], &matrix[i][matrixCol - j - 1]);
        }
    }

    for (i = 0; i < matrixRow; ++i) {
        for (j = 0; j < matrixCol - i; ++j) {
            swap(&matrix[i][j], &matrix[matrixCol - 1 - j][matrixCol - 1 - i]);
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
    } testCase[] = {{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 3, {3, 3, 3}},
                    {{{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}}, 4, {4, 4, 4, 4}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
     *  Output: [[7,4,1],[8,5,2],[9,6,3]]
     *
     *  Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
     *  Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
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
        rotate(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize);
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
