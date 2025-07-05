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
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int findLucky(int *arr, int arrSize) {
    int retVal = -1;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int key;
    for (int i = 0; i < arrSize; ++i) {
        key = arr[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = key;
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value += 1;
        }
    }

    struct hashTable *pCurrent = NULL;
    pTemp = NULL;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        if (pCurrent->key == pCurrent->value) {
            retVal = fmax(retVal, pCurrent->key);
        }
        HASH_DEL(pHashTable, pCurrent);
        free(pCurrent);
        pCurrent = NULL;
    }

    //
    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{2, 2, 3, 4}, 4}, {{1, 2, 2, 3, 3, 3}, 6}, {{2, 2, 2, 3, 3}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [2,2,3,4]
     *  Output: 2
     *
     *  Input: arr = [1,2,2,3,3,3]
     *  Output: 3
     *
     *  Input: arr = [2,2,2,3,3]
     *  Output: -1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = findLucky(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
