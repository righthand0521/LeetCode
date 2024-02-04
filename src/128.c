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
int updateHashTable(struct hashTable **pHashTable, int key, int value) {
    int retVal = EXIT_SUCCESS;

    struct hashTable *pTemp = NULL;
    HASH_FIND_INT((*pHashTable), &key, pTemp);
    if (pTemp != NULL) {
        pTemp->value = value;
    } else {
        pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            retVal = EXIT_FAILURE;
            return retVal;
        }
        pTemp->key = key;
        pTemp->value = value;
        HASH_ADD_INT((*pHashTable), key, pTemp);
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
int longestConsecutive(int *nums, int numsSize) {
    int retVal = 0;

    //
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int key;
    int left, right, length;
    int i;
    for (i = 0; i < numsSize; ++i) {
        key = nums[i];
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            continue;
        }

        //
        left = 0;
        key = nums[i] - 1;
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            left = pTemp->value;
        }

        right = 0;
        key = nums[i] + 1;
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            right = pTemp->value;
        }

        //
        length = left + right + 1;

        key = nums[i];
        if (updateHashTable(&pHashTable, key, 1) == EXIT_FAILURE) {
            goto exit;
        }

        key = nums[i] - left;
        if (updateHashTable(&pHashTable, key, length) == EXIT_FAILURE) {
            goto exit;
        }

        key = nums[i] + right;
        if (updateHashTable(&pHashTable, key, length) == EXIT_FAILURE) {
            goto exit;
        }

        //
        retVal = fmax(retVal, length);
    }

exit:
    //
    freeAll(pHashTable);
    pHashTable = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{100, 4, 200, 1, 3, 2}, 6}, {{0, 3, 7, 2, 5, 8, 4, 6, 0, 1}, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [100,4,200,1,3,2]
     *  Output: 4
     *
     *  Input: nums = [0,3,7,2,5,8,4,6,0,1]
     *  Output: 9
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = longestConsecutive(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
