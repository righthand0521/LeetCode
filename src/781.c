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
int numRabbits(int *answers, int answersSize) {
    int retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    for (int i = 0; i < answersSize; i++) {
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &answers[i], pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = answers[i];
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value++;
        }
    }

    pTemp = NULL;
    struct hashTable *pCurrent;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        retVal += ((pCurrent->value + pCurrent->key) / (pCurrent->key + 1) * (pCurrent->key + 1));
        HASH_DEL(pHashTable, pCurrent);
        free(pCurrent);
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int answers[MAX_SIZE];
        int answersSize;
    } testCase[] = {{{1, 1, 2}, 3}, {{10, 10, 10}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: answers = [1,1,2]
     *  Output: 5
     *
     *  Input: answers = [10,10,10]
     *  Output: 11
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: answers = [");
        for (j = 0; j < testCase[i].answersSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].answers[j]);
        }
        printf("]\n");

        answer = numRabbits(testCase[i].answers, testCase[i].answersSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
