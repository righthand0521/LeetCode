#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* pNum1, int* pNum2) {
    int temp = *pNum1;
    *pNum1 = *pNum2;
    *pNum2 = temp;
}
void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    int i, j;

    for (i = 0; i < matrixSize; ++i) {
        for (j = 0; j < (*matrixColSize / 2); ++j) {
            swap(&matrix[i][j], &matrix[i][*matrixColSize - j - 1]);
        }
    }

    for (i = 0; i < matrixSize; ++i) {
        for (j = 0; j < *matrixColSize - i; ++j) {
            swap(&matrix[i][j], &matrix[*matrixColSize - 1 - j][matrixSize - 1 - i]);
        }
    }
}

int main(int argc, char** argv) {
#define MAX_ROW (200)
#define MAX_COLUMN (200)
    struct testCaseType {
        int matrix[MAX_ROW][MAX_COLUMN];
        int matrixSize;
        int matrixColSize;
    } testCase[] = {{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 3, 3},
                    {{{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}}, 4, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pMatrix = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: matrix = \n");
        printf("       [");
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            printf("%s\n         [", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].matrixColSize; ++k) {
                printf("%s%2d", (k == 0 ? "" : ","), testCase[i].matrix[j][k]);
            }
            printf("]");
        }
        printf("\n       ]\n");

        pMatrix = (int**)malloc(testCase[i].matrixSize * sizeof(int*));
        if (pMatrix == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            pMatrix[j] = (int*)malloc(testCase[i].matrixColSize * sizeof(int));
            if (pMatrix[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pMatrix[k]);
                }
                free(pMatrix);
                return EXIT_FAILURE;
            }
            memset(pMatrix[j], 0, (testCase[i].matrixColSize * sizeof(int)));
            memcpy(pMatrix[j], testCase[i].matrix[j], (testCase[i].matrixColSize * sizeof(int)));
        }
        rotate(pMatrix, testCase[i].matrixSize, &(testCase[i].matrixColSize));
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
