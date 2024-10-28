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
int longestSquareStreak(int *nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int root, squareStreak;
    int i;
    for (i = 0; i < numsSize; ++i) {
        root = (int)sqrt(nums[i]);
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &root, pTemp);
        if ((root * root == nums[i]) && (pTemp != NULL)) {
            squareStreak = pTemp->value + 1;
        } else {
            squareStreak = 1;
        }

        root = nums[i];
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &root, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = root;
            pTemp->value = squareStreak;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value = squareStreak;
        }
    }

    struct hashTable *pCurrent = NULL;
    pTemp = NULL;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        retVal = fmax(retVal, pHashTable->value);
        HASH_DEL(pHashTable, pCurrent);
        free(pCurrent);
    }
    if (retVal == 1) {
        retVal = -1;  // return -1 if there is no square streak.
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{4, 3, 6, 16, 8, 2}, 6}, {{2, 3, 5, 6, 7}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,3,6,16,8,2]
     *  Output: 3
     *
     *  Input: nums = [2,3,5,6,7]
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = longestSquareStreak(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
