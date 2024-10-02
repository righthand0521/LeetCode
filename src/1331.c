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
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *arrayRankTransform(int *arr, int arrSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    if (arrSize == 0) {
        return pRetVal;
    }

    pRetVal = (int *)calloc(arrSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    memcpy(pRetVal, arr, (arrSize * sizeof(int)));
    qsort(pRetVal, arrSize, sizeof(int), compareInteger);

    int rank = 1;
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        pHashTable = NULL;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    pTemp->key = pRetVal[0];
    pTemp->value = rank;
    HASH_ADD_INT(pHashTable, key, pTemp);

    int i;
    for (i = 1; i < arrSize; ++i) {
        if (pRetVal[i] > pRetVal[i - 1]) {
            rank++;
        }
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &pRetVal[i], pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                pHashTable = NULL;
                free(pRetVal);
                pRetVal = NULL;
                return pRetVal;
            }
            pTemp->key = pRetVal[i];
            pTemp->value = rank;
            HASH_ADD_INT(pHashTable, key, pTemp);
        }
    }

    for (i = 0; i < arrSize; ++i) {
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &arr[i], pTemp);
        pRetVal[(*returnSize)++] = pTemp->value;
    }

    //
    freeAll(pHashTable);

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int returnSize;
    } testCase[] = {{{40, 10, 20, 30}, 4, 0}, {{100, 100, 100}, 3, 0}, {{37, 12, 28, 9, 100, 56, 80, 5, 12}, 9, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [40,10,20,30]
     *  Output: [4,1,2,3]
     *
     *  Input: arr = [100,100,100]
     *  Output: [1,1,1]
     *
     *  Input: arr = [37,12,28,9,100,56,80,5,12]
     *  Output: [5,3,4,2,8,6,7,1,3]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        pAnswer = arrayRankTransform(testCase[i].arr, testCase[i].arrSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
