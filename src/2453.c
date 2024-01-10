#include <limits.h>
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
int destroyTargets(int *nums, int numsSize, int space) {
    int retVal = INT_MAX;

    struct hashTable *pCount = NULL;
    struct hashTable *pTmp;
    int maxTarget = 0;
    int key, value;
    int i;
    for (i = 0; i < numsSize; ++i) {
        key = nums[i] % space;
        value = 0;

        pTmp = NULL;
        HASH_FIND_INT(pCount, &key, pTmp);
        if (pTmp != NULL) {
            value = pTmp->value;
        }

        key = nums[i] % space;
        pTmp = NULL;
        HASH_FIND_INT(pCount, &key, pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pCount);
                return retVal;
            }
            pTmp->key = key;
            pTmp->value = value + 1;
            HASH_ADD_INT(pCount, key, pTmp);
        } else {
            pTmp->value = value + 1;
        }

        maxTarget = fmax(maxTarget, value + 1);
    }
    for (i = 0; i < numsSize; ++i) {
        key = nums[i] % space;
        value = 0;

        pTmp = NULL;
        HASH_FIND_INT(pCount, &key, pTmp);
        if (pTmp != NULL) {
            value = pTmp->value;
        }
        if (value == maxTarget) {
            retVal = fmin(retVal, nums[i]);
        }
    }
    freeAll(pCount);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int space;
    } testCase[] = {{{3, 7, 8, 1, 1, 5}, 6, 2}, {{1, 3, 5, 2, 4, 6}, 6, 2}, {{6, 2, 5}, 3, 100}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,7,8,1,1,5], space = 2
     *  Output: 1
     *
     *  Input: nums = [1,3,5,2,4,6], space = 2
     *  Output: 1
     *
     *  Input: nums = [6,2,5], space = 100
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], space = %d\n", testCase[i].space);

        answer = destroyTargets(testCase[i].nums, testCase[i].numsSize, testCase[i].space);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
