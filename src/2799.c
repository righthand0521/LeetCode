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
        // printf("%d: %d\n", current->key, current->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int countCompleteSubarrays(int *nums, int numsSize) {
    int retVal = 0;

    struct hashTable *pDistinct = NULL;
    struct hashTable *pTemp;
    int key;
    for (int i = 0; i < numsSize; i++) {
        key = nums[i];
        pTemp = NULL;
        HASH_FIND_INT(pDistinct, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pDistinct);
                return retVal;
            }
            pTemp->key = key;
            pTemp->value = 1;
            HASH_ADD_INT(pDistinct, key, pTemp);
        }
    }
    int distinctSize = HASH_COUNT(pDistinct);

    struct hashTable *pHashTable = NULL;
    int pHashTableSize;
    int remove, add;
    int right = 0;
    for (int left = 0; left < numsSize; left++) {
        if (left > 0) {
            remove = nums[left - 1];
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &remove, pTemp);
            if (pTemp == NULL) {
                pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
                if (pTemp == NULL) {
                    perror("malloc");
                    freeAll(pHashTable);
                    freeAll(pDistinct);
                    return retVal;
                }
                pTemp->key = remove;
                pTemp->value = -1;
                HASH_ADD_INT(pHashTable, key, pTemp);
            } else {
                pTemp->value -= 1;
            }

            if (pTemp->value == 0) {
                HASH_DEL(pHashTable, pTemp);
                free(pTemp);
            }
        }

        pHashTableSize = HASH_COUNT(pHashTable);
        while (right < numsSize) {
            if (pHashTableSize >= distinctSize) {
                break;
            }

            add = nums[right];
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &add, pTemp);
            if (pTemp == NULL) {
                pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
                if (pTemp == NULL) {
                    perror("malloc");
                    freeAll(pHashTable);
                    freeAll(pDistinct);
                    return retVal;
                }
                pTemp->key = add;
                pTemp->value = 1;
                HASH_ADD_INT(pHashTable, key, pTemp);
            } else {
                pTemp->value += 1;
            }
            pHashTableSize = HASH_COUNT(pHashTable);

            right++;
        }

        if (pHashTableSize == distinctSize) {
            retVal += (numsSize - right + 1);
        }
    }

    //
    freeAll(pHashTable);
    freeAll(pDistinct);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3, 1, 2, 2}, 5}, {{5, 5, 5, 5}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,1,2,2]
     *  Output: 4
     *
     *  Input: nums = [5,5,5,5]
     *  Output: 10
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = countCompleteSubarrays(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
