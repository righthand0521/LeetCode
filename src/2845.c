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
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
long long countInterestingSubarrays(int *nums, int numsSize, int modulo, int k) {
    long long retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        return retVal;
    }
    pTemp->key = 0;
    pTemp->value = 1;
    HASH_ADD_INT(pHashTable, key, pTemp);

    int key;
    int prefix = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % modulo == k) {
            prefix++;
        }

        key = (prefix - k + modulo) % modulo;
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            retVal += pTemp->value;
        }

        key = prefix % modulo;
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

    //
    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int modulo;
        int k;
    } testCase[] = {{{3, 2, 4}, 3, 2, 1}, {{3, 1, 9, 6}, 4, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,2,4], modulo = 2, k = 1
     *  Output: 3
     *
     *  Input: nums = [3,1,9,6], modulo = 3, k = 0
     *  Output: 2
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], modulo = %d, k = %d\n", testCase[i].modulo, testCase[i].k);

        answer = countInterestingSubarrays(testCase[i].nums, testCase[i].numsSize, testCase[i].modulo, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
