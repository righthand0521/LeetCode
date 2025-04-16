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
long long countGood(int *nums, int numsSize, int k) {
    long long retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int key;

    int same = 0;
    int right = -1;
    for (int left = 0; left < numsSize; ++left) {
        while ((same < k) && (right + 1 < numsSize)) {
            ++right;

            pTemp = NULL;
            key = nums[right];
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
                same += pTemp->value;
                pTemp->value += 1;
            }
        }

        if (same >= k) {
            retVal += (numsSize - right);
        }

        pTemp = NULL;
        key = nums[left];
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = key;
            pTemp->value = -1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value -= 1;
            same -= pTemp->value;
        }
    }

    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 1, 1, 1, 1}, 5, 10}, {{3, 1, 4, 3, 2, 2, 4}, 7, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,1,1,1], k = 10
     *  Output: 1
     *
     *  Input: nums = [3,1,4,3,2,2,4], k = 2
     *  Output: 4
     */

    long long answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = countGood(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
