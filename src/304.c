#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int** sums;
    int sumsSize;
} NumMatrix;
NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize) {
    NumMatrix* pCreate = (NumMatrix*)malloc(sizeof(NumMatrix));
    if (pCreate == NULL) {
        perror("malloc");
        return pCreate;
    }

    pCreate->sumsSize = matrixSize + 1;
    pCreate->sums = (int**)malloc((matrixSize + 1) * sizeof(int*));
    if (pCreate->sums == NULL) {
        perror("malloc");
        free(pCreate);
        pCreate = NULL;
        return pCreate;
    }

    int n = matrixSize ? matrixColSize[0] : 0;
    int i, j;
    for (i = 0; i <= matrixSize; i++) {
        pCreate->sums[i] = (int*)malloc((n + 1) * sizeof(int));
        if (pCreate->sums[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pCreate->sums[j]);
                pCreate->sums[j] = NULL;
            }
            free(pCreate->sums);
            pCreate->sums = NULL;
            free(pCreate);
            pCreate = NULL;
            return pCreate;
        }
        memset(pCreate->sums[i], 0, ((n + 1) * sizeof(int)));
    }

    for (i = 0; i < matrixSize; ++i) {
        for (j = 0; j < matrixColSize[i]; ++j) {
            pCreate->sums[i + 1][j + 1] =
                pCreate->sums[i][j + 1] + pCreate->sums[i + 1][j] - pCreate->sums[i][j] + matrix[i][j];
        }
    }

    return pCreate;
}
int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) {
    int retVal = 0;

    if (obj == NULL) {
        return retVal;
    }
    retVal =
        obj->sums[row2 + 1][col2 + 1] - obj->sums[row1][col2 + 1] - obj->sums[row2 + 1][col1] + obj->sums[row1][col1];

    return retVal;
}
void numMatrixFree(NumMatrix* obj) {
    if (obj == NULL) {
        return;
    }

    int i;
    for (i = 0; i < obj->sumsSize; ++i) {
        free(obj->sums[i]);
        obj->sums[i] = NULL;
    }
    free(obj->sums);
    obj->sums = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your NumMatrix struct will be instantiated and called as such:
 * NumMatrix* obj = numMatrixCreate(matrix, matrixSize, matrixColSize);
 * int param_1 = numMatrixSumRegion(obj, row1, col1, row2, col2);

 * numMatrixFree(obj);
*/

int main(int argc, char** argv) {
#if 0
#define MAX_SIZE (100)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][MAX_SIZE];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"NumMatrix", "sumRegion", "sumRegion", "sumRegion"},
                     {{{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}},
                      {{2, 1, 4, 3}},
                      {{1, 1, 2, 2}},
                      {{1, 2, 2, 4}}},
                     {5, 4, 4, 4},
                     4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    NumMatrix* obj = NULL;
    int retInt;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[", (j == 0) ? "" : ", ");
            for (k = 0; k < testCase[i].valSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ", ", testCase[i].val[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "NumMatrix") == 0) {
                obj = numMatrixCreate(testCase[i].val[j], testCase[i].valSize[j], testCase[i].valSize[j]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "sumRegion") == 0) {
                retInt = numMatrixSumRegion(obj, testCase[i].val[j][0], testCase[i].val[j][1]);
                printf("%s%d", (j == 0) ? "" : ", ", retInt);
            }
        }
        printf("]\n");

        numMatrixFree(obj);
        obj = NULL;

        printf("\n");
    }
#endif

    return EXIT_SUCCESS;
}
