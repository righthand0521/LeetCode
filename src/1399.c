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
        // printf("%d: %d\n", current->key, current->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int countLargestGroup(int n) {
    int retVal = 0;

    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int key;
    int num;
    int maxValue = 0;
    for (int i = 1; i <= n; ++i) {
        key = 0;
        num = i;
        while (num) {
            key += num % 10;
            num /= 10;
        }

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
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value += 1;
        }

        maxValue = fmax(maxValue, pTemp->value);
    }

    pTemp = NULL;
    struct hashTable* pCurrent = NULL;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        if (pCurrent->value == maxValue) {
            ++retVal;
        }
        HASH_DEL(pHashTable, pCurrent);
        free(pCurrent);
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{13}, {2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 13
     *  Output: 4
     *
     *  Input: n = 2
     *  Output: 2
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = countLargestGroup(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
