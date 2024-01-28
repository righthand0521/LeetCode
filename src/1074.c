#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int subarraySum(int *prefixSumList, int prefixSumListSize, int target) {
    int retVal = 0;

    struct hashTable *pPrefixSumMap = NULL;
    struct hashTable *pTmp = NULL;
    pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTmp == NULL) {
        perror("malloc");
        goto exit;
    }
    pTmp->key = 0;
    pTmp->value = 1;
    HASH_ADD_INT(pPrefixSumMap, key, pTmp);

    int prefixSum = 0;
    int sum;
    int i;
    for (i = 0; i < prefixSumListSize; ++i) {
        prefixSum += prefixSumList[i];

        sum = prefixSum - target;
        pTmp = NULL;
        HASH_FIND_INT(pPrefixSumMap, &sum, pTmp);
        if (pTmp != NULL) {
            retVal += pTmp->value;
        }

        sum = prefixSum;
        pTmp = NULL;
        HASH_FIND_INT(pPrefixSumMap, &sum, pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTmp->key = sum;
            pTmp->value = 1;
            HASH_ADD_INT(pPrefixSumMap, key, pTmp);
        } else {
            pTmp->value += 1;
        }
    }

exit:
    //
    freeAll(pPrefixSumMap);
    pPrefixSumMap = NULL;

    return retVal;
}
int numSubmatrixSumTarget(int **matrix, int matrixSize, int *matrixColSize, int target) {
    int retVal = 0;

    int rowSize = matrixSize;
    int colSize = matrixColSize[0];

    int prefixSumSize = colSize;
    int prefixSum[colSize];
    int row, x, y;
    for (row = 0; row < rowSize; ++row) {
        memset(prefixSum, 0, sizeof(prefixSum));
        for (x = row; x < rowSize; ++x) {
            for (y = 0; y < colSize; ++y) {
                prefixSum[y] += matrix[x][y];
            }
            retVal += subarraySum(prefixSum, prefixSumSize, target);
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_ROW (100)
#define MAX_COLUMN (100)
    struct testCaseType {
        int matrix[MAX_ROW][MAX_COLUMN];
        int matrixSize;
        int matrixColSize[MAX_ROW];
        int target;
    } testCase[] = {
        {{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}, 3, {3, 3, 3}, 0}, {{{1, -1}, {-1, 1}}, 2, {2, 2}, 0}, {{{904}}, 1, {1}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
     *  Output: 4
     *
     *  Input: matrix = [[1,-1],[-1,1]], target = 0
     *  Output: 5
     *
     *  Input: matrix = [[904]], target = 0
     *  Output: 0
     */

    int **pMatrix = NULL;
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
        printf("], target = %d\n", testCase[i].target);

        pMatrix = (int **)malloc(testCase[i].matrixSize * sizeof(int *));
        if (pMatrix == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            pMatrix[j] = (int *)malloc(testCase[i].matrixColSize[j] * sizeof(int));
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
        answer = numSubmatrixSumTarget(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize, testCase[i].target);
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
