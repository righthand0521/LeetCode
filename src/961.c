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
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int repeatedNTimes(int* nums, int numsSize) {
    int retVal = 0;

    struct hashTable* pHashTable = NULL;
    struct hashTable* pEntry = NULL;
    for (int i = 0; i < numsSize; ++i) {
        HASH_FIND_INT(pHashTable, &nums[i], pEntry);
        if (pEntry == NULL) {
            pEntry = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pEntry == NULL) {
                freeAll(pHashTable);
                return retVal;
            }
            pEntry->key = nums[i];
            pEntry->value = 1;
            HASH_ADD_INT(pHashTable, key, pEntry);
        } else {
            retVal = nums[i];
            break;
        }
    }

    //
    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 3}, 4}, {{2, 1, 2, 5, 3, 2}, 6}, {{5, 1, 5, 2, 5, 3, 5, 4}, 8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,3]
     *  Output: 3
     *
     *  Input: nums = [2,1,2,5,3,2]
     *  Output: 2
     *
     *  Input: nums = [5,1,5,2,5,3,5,4]
     *  Output: 5
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = repeatedNTimes(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
