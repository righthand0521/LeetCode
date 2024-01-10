#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Count {
    int soldiers;
    int index;
};
int compareStruct(const void* a1, const void* a2) {
    struct Count* p1 = (struct Count*)a1;
    struct Count* p2 = (struct Count*)a2;

    // ascending order
    if (p1->soldiers == p2->soldiers) {
        return (p1->index > p2->index);
    } else {
        return (p1->soldiers > p2->soldiers);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* kWeakestRows(int** mat, int matSize, int* matColSize, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    struct Count value[matSize];
    memset(value, 0, sizeof(value));
    int soldiers;
    int row, col;
    for (row = 0; row < matSize; ++row) {
        soldiers = 0;
        for (col = 0; col < matColSize[row]; ++col) {
            if (mat[row][col] == 0) {
                break;
            }
            soldiers++;
        }
        value[row].soldiers = soldiers;
        value[row].index = row;
    }
    qsort(value, matSize, sizeof(struct Count), compareStruct);

    pRetVal = (int*)malloc(matSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (matSize * sizeof(int)));

    int i;
    for (i = 0; i < k; ++i) {
        pRetVal[i] = value[i].index;
        (*returnSize)++;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int mat[MAX_SIZE][MAX_SIZE];
        int matSize;
        int matColSize[MAX_SIZE];
        int k;
        int returnSize;
    } testCase[] = {{{{1, 1, 0, 0, 0}, {1, 1, 1, 1, 0}, {1, 0, 0, 0, 0}, {1, 1, 0, 0, 0}, {1, 1, 1, 1, 1}},
                     5,
                     {5, 5, 5, 5, 5},
                     3,
                     0},
                    {{{1, 0, 0, 0}, {1, 1, 1, 1}, {1, 0, 0, 0}, {1, 0, 0, 0}}, 4, {4, 4, 4, 4}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: mat =Input: mat = [[1,1,0,0,0], [1,1,1,1,0], [1,0,0,0,0], [1,1,0,0,0], [1,1,1,1,1]], k = 3
     *  Output: [2,0,3]
     *
     *  Input: mat = [[1,0,0,0], [1,1,1,1], [1,0,0,0], [1,0,0,0]], k = 2
     *  Output: [0,2]
     */

    int** pMat = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: mat =  [");
        for (j = 0; j < testCase[i].matSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].matColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].mat[j][k]);
            }
            printf("]");
        }
        printf("], k= %d\n", testCase[i].k);

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
        pAnswer =
            kWeakestRows(pMat, testCase[i].matSize, testCase[i].matColSize, testCase[i].k, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].matSize; ++j) {
            if (pMat[j]) {
                free(pMat[j]);
                pMat[j] = NULL;
            }
        }
        free(pMat);
        pMat = NULL;
    }

    return EXIT_SUCCESS;
}
