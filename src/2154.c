#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define HASH_TABLE_SIZE (1)
#if (HASH_TABLE_SIZE)
struct hashTable {
    int key;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
#else
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#endif
int findFinalValue(int* nums, int numsSize, int original) {
#if (HASH_TABLE_SIZE)
    int retVal = 0;

    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int key;
    for (int i = 0; i < numsSize; ++i) {
        key = nums[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            continue;
        }
        pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            freeAll(pHashTable);
            return retVal;
        }
        pTemp->key = key;
        HASH_ADD_INT(pHashTable, key, pTemp);
    }
    while (1) {
        key = original;
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            original *= 2;
        } else {
            break;
        }
    }
    retVal = original;
    //
    freeAll(pHashTable);
#else
    int retVal = original;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == retVal) {
            retVal *= 2;
        }
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int original;
    } testCase[] = {{{5, 3, 6, 1, 12}, 5, 3}, {{2, 7, 9}, 3, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [5,3,6,1,12], original = 3
     *  Output: 24
     *
     *  Input: nums = [2,7,9], original = 4
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], original = %d\n", testCase[i].original);

        answer = findFinalValue(testCase[i].nums, testCase[i].numsSize, testCase[i].original);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
