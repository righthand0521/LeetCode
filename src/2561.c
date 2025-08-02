#include <limits.h>
#include <math.h>
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
bool updateFrequency(struct hashTable **pObj, int key, int value) {
    bool retVal = true;

    struct hashTable *pTemp = NULL;
    HASH_FIND_INT(*pObj, &key, pTemp);
    if (pTemp == NULL) {
        pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            retVal = false;
        } else {
            pTemp->key = key;
            pTemp->value = value;
            HASH_ADD_INT(*pObj, key, pTemp);
        }
    } else {
        pTemp->value += value;
    }

    return retVal;
}
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
long long minCost(int *basket1, int basket1Size, int *basket2, int basket2Size) {
    long long retVal = 0;

    struct hashTable *frequency = NULL;
    int minValue = INT_MAX;
    for (int i = 0; i < basket1Size; i++) {
        updateFrequency(&frequency, basket1[i], 1);
        minValue = fmin(minValue, basket1[i]);
    }
    for (int i = 0; i < basket2Size; i++) {
        updateFrequency(&frequency, basket2[i], -1);
        minValue = fmin(minValue, basket2[i]);
    }

    int merge[basket1Size + basket2Size];
    memset(merge, 0, sizeof(merge));
    int mergeSize = 0;
    struct hashTable *pCurrent;
    struct hashTable *pTmp;
    HASH_ITER(hh, frequency, pCurrent, pTmp) {
        int c = pCurrent->value;
        if (c % 2 != 0) {
            freeAll(frequency);
            retVal = -1;
            return retVal;
        }

        for (int i = 0; i < abs(c) / 2; i++) {
            merge[mergeSize++] = pCurrent->key;
        }
    }

    if (mergeSize == 0) {
        freeAll(frequency);
        return retVal;
    }
    qsort(merge, mergeSize, sizeof(int), compareInteger);

    for (int i = 0; i < mergeSize / 2; i++) {
        retVal += fmin(merge[i], minValue * 2);
    }

    //
    freeAll(frequency);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int basket1[MAX_SIZE];
        int basket1Size;
        int basket2[MAX_SIZE];
        int basket2Size;
    } testCase[] = {{{4, 2, 2, 2}, 4, {1, 4, 1, 2}, 4}, {{2, 3, 4, 1}, 4, {3, 2, 5, 1}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
     *  Output: 1
     *
     *  Input: basket1 = [2,3,4,1], basket2 = [3,2,5,1]
     *  Output: -1
     */

    int i, j;
    long long answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: basket1 = [");
        for (j = 0; j < testCase[i].basket1Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].basket1[j]);
        }
        printf("], basket2 = [");
        for (j = 0; j < testCase[i].basket2Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].basket2[j]);
        }
        printf("]\n");

        answer = minCost(testCase[i].basket1, testCase[i].basket1Size, testCase[i].basket2, testCase[i].basket2Size);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
