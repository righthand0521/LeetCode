#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int minOperations(int *nums, int numsSize, int k) {
    int retVal = -1;  // If it is impossible to make all elements equal to k, return -1.

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int key;
    for (int i = 0; i < numsSize; i++) {
        key = nums[i];
        if (key < k) {
            freeAll(pHashTable);
            return retVal;
        } else if (key > k) {
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &key, pTemp);
            if (pTemp != NULL) {
                continue;
            }

            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = key;
            HASH_ADD_INT(pHashTable, key, pTemp);
        }
    }
    retVal = HASH_COUNT(pHashTable);
    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{5, 2, 5, 4, 5}, 5, 2}, {{2, 1, 2}, 3, 2}, {{9, 7, 5, 3}, 4, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [5,2,5,4,5], k = 2
     *  Output: 2
     *
     *  Input: nums = [2,1,2], k = 2
     *  Output: -1
     *
     *  Input: nums = [9,7,5,3], k = 1
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = minOperations(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
