#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
int getValue(struct hashTable* pObj, int x) {
    int retVal = 0;

    struct hashTable* pTmp = NULL;
    HASH_FIND_INT(pObj, &x, pTmp);
    if (pTmp != NULL) {
        retVal = pTmp->value;
    }

    return retVal;
}
void addValue(struct hashTable** pObj, int x, int y) {
    struct hashTable* pTmp = NULL;
    HASH_FIND_INT(*pObj, &x, pTmp);
    if (pTmp == NULL) {
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            return;
        }
        pTmp->key = x;
        pTmp->value = y;
        HASH_ADD_INT(*pObj, key, pTmp);
    } else {
        pTmp->value += y;
    }
}
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int countTriplets(int* arr, int arrSize) {
    int retVal = 0;

    // Maps to store counts and totals of XOR values encountered
    struct hashTable* pCountHashTable = NULL;
    addValue(&pCountHashTable, 0, 1);
    struct hashTable* pTotalHashTable = NULL;

    // Iterating through the array
    int prefix = 0;
    int i;
    for (i = 0; i < arrSize; ++i) {
        // Calculating XOR prefix
        prefix ^= arr[i];

        // Calculating contribution of current element to the result
        retVal += getValue(pCountHashTable, prefix) * i - getValue(pTotalHashTable, prefix);

        // Updating total count of current XOR value
        addValue(&pTotalHashTable, prefix, i + 1);
        addValue(&pCountHashTable, prefix, 1);
    }

    //
    freeAll(pCountHashTable);
    pCountHashTable = NULL;
    freeAll(pTotalHashTable);
    pTotalHashTable = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{2, 3, 1, 6, 7}, 5}, {{1, 1, 1, 1, 1}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [2,3,1,6,7]
     *  Output: 4
     *
     *  Input: arr = [1,1,1,1,1]
     *  Output: 10
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = countTriplets(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
