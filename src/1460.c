#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void addValue(struct hashTable** pObj, int key, int value) {
    struct hashTable* pTmp = NULL;
    HASH_FIND_INT(*pObj, &key, pTmp);
    if (pTmp == NULL) {
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            return;
        }
        pTmp->key = key;
        pTmp->value = 1;
        HASH_ADD_INT(*pObj, key, pTmp);
    } else {
        pTmp->value += value;
    }
}
bool canBeEqual(int* target, int targetSize, int* arr, int arrSize) {
    bool retVal = true;

    struct hashTable* pCountHashTable = NULL;
    int i;
    for (i = 0; i < targetSize; ++i) {
        addValue(&pCountHashTable, target[i], 1);
    }
    for (i = 0; i < arrSize; ++i) {
        addValue(&pCountHashTable, arr[i], -1);
    }

    struct hashTable* pCurrent = NULL;
    struct hashTable* pTmp = NULL;
    HASH_ITER(hh, pCountHashTable, pCurrent, pTmp) {
        if (pCountHashTable->value != 0) {
            retVal = false;
        }
        HASH_DEL(pCountHashTable, pCurrent);
        free(pCurrent);
        pCurrent = NULL;
    }
    pTmp = NULL;
    pCountHashTable = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int target[MAX_SIZE];
        int targetSize;
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{1, 2, 3, 4}, 4, {2, 4, 1, 3}, 4}, {{7}, 1, {7}, 1}, {{3, 7, 9}, 3, {3, 7, 11}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: target = [1,2,3,4], arr = [2,4,1,3]
     *  Output: true
     *
     *  Input: target = [7], arr = [7]
     *  Output: true
     *
     *  Input: target = [3,7,9], arr = [3,7,11]
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: target = [");
        for (j = 0; j < testCase[i].targetSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].target[j]);
        }
        printf("], arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = canBeEqual(testCase[i].target, testCase[i].targetSize, testCase[i].arr, testCase[i].arrSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
