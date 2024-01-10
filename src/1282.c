#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int* value;
    int valueSize;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d; ", pFree->key, pFree->valueSize);
        // for (int i = 0; i < pFree->valueSize; ++i) {
        //     printf("%d ", pFree->value[i]);
        // }
        // printf("\n");

        free(pFree->value);
        pFree->value = NULL;
        HASH_DEL(pFree, current);
        free(current);
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** groupThePeople(int* groupSizes, int groupSizesSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    int i, j;

    //
    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int value;
    for (i = 0; i < groupSizesSize; ++i) {
        value = groupSizes[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &value, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return pRetVal;
            }
            pTemp->key = value;
            pTemp->value = (int*)malloc(groupSizesSize * sizeof(int));
            memset(pTemp->value, 0, (groupSizesSize * sizeof(int)));
            pTemp->value[0] = i;
            pTemp->valueSize = 1;

            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value[pTemp->valueSize] = i;
            pTemp->valueSize += 1;
        }
    }

    //
    (*returnColumnSizes) = (int*)malloc(groupSizesSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (groupSizesSize * sizeof(int)));
    pRetVal = (int**)malloc(groupSizesSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        freeAll(pHashTable);
        return pRetVal;
    }

    //
    int groupSize;
    struct hashTable* pCurrent;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        groupSize = pCurrent->valueSize / pCurrent->key;
        for (i = 0; i < groupSize; ++i) {
            pRetVal[(*returnSize)] = (int*)malloc(pCurrent->key * sizeof(int));
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                for (j = 0; j < (*returnSize); ++j) {
                    free(pRetVal[j]);
                    pRetVal[j] = NULL;
                }
                free((*returnColumnSizes));
                (*returnColumnSizes) = NULL;
                freeAll(pHashTable);
                (*returnSize) = 0;
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (pCurrent->key * sizeof(int)));
            for (j = 0; j < pCurrent->key; ++j) {
                pRetVal[(*returnSize)][j] = pCurrent->value[j + (pCurrent->key * i)];
            }
            (*returnColumnSizes)[(*returnSize)] = pCurrent->key;
            (*returnSize)++;
        }
    }

    //
    freeAll(pHashTable);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int groupSizes[MAX_SIZE];
        int groupSizesSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{3, 3, 3, 3, 3, 1, 3}, 7, 0, NULL}, {{2, 1, 3, 3, 3, 2}, 6, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: groupSizes = [3,3,3,3,3,1,3]
     *  Output: [[5],[0,1,2],[3,4,6]]
     *
     *  Input: groupSizes = [2,1,3,3,3,2]
     *  Output: [[1],[0,5],[2,3,4]]
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: groupSizes = [");
        for (j = 0; j < testCase[i].groupSizesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].groupSizes[j]);
        }
        printf("]\n");

        pAnswer = groupThePeople(testCase[i].groupSizes, testCase[i].groupSizesSize, &testCase[i].returnSize,
                                 &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
    }

    return EXIT_SUCCESS;
}
