#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int firstCompleteIndex(int* arr, int arrSize, int** mat, int matSize, int* matColSize) {
    int retVal = 0;

    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int key;
    for (int i = 0; i < arrSize; ++i) {
        key = arr[i];
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = key;
            pTemp->value = i;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value = i;
        }
    }

    int rowSize = matSize;
    int colSize = matColSize[0];
    retVal = INT_MAX;
    int lastElementIndex, indexVal;
    for (int row = 0; row < rowSize; row++) {
        lastElementIndex = INT_MIN;
        for (int col = 0; col < colSize; col++) {
            indexVal = lastElementIndex;
            key = mat[row][col];
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &key, pTemp);
            if (pTemp != NULL) {
                indexVal = pTemp->value;
            }
            lastElementIndex = fmax(lastElementIndex, indexVal);
        }
        retVal = fmin(retVal, lastElementIndex);
    }
    for (int col = 0; col < colSize; col++) {
        lastElementIndex = INT_MIN;
        for (int row = 0; row < rowSize; row++) {
            indexVal = lastElementIndex;
            key = mat[row][col];
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &key, pTemp);
            if (pTemp != NULL) {
                indexVal = pTemp->value;
            }
            lastElementIndex = fmax(lastElementIndex, indexVal);
        }
        retVal = fmin(retVal, lastElementIndex);
    }

    //
    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e3)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int mat[MAX_SIZE][MAX_SIZE];
        int matSize;
        int matColSize[MAX_SIZE];
    } testCase[] = {{{1, 3, 4, 2}, 4, {{1, 4}, {2, 3}}, 2, {2, 2}},
                    {{2, 8, 7, 4, 1, 3, 5, 6, 9}, 9, {{3, 2, 5}, {1, 4, 6}, {8, 7, 9}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
     *  Output: 2
     *
     *  Input: arr = [2,8,7,4,1,3,5,6,9], mat = [[3,2,5],[1,4,6],[8,7,9]]
     *  Output: 3
     */

    int** pMat = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("], mat = [");
        for (j = 0; j < testCase[i].matSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].matColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].mat[j][k]);
            }
            printf("]");
        }
        printf("]\n");

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
        answer =
            firstCompleteIndex(testCase[i].arr, testCase[i].arrSize, pMat, testCase[i].matSize, testCase[i].matColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (k = 0; k < testCase[i].matSize; ++k) {
            if (pMat[k]) {
                free(pMat[k]);
                pMat[k] = NULL;
            }
        }
        free(pMat);
        pMat = NULL;
    }

    return EXIT_SUCCESS;
}
