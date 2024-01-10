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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 2;
    pRetVal = (int *)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int complement;
    int i;
    for (i = 0; i < numsSize; ++i) {
        complement = target - nums[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &complement, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                free(pRetVal);
                pRetVal = NULL;
                (*returnSize) = 0;
                return pRetVal;
            }
            pTemp->key = nums[i];
            pTemp->value = i;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            *(pRetVal + 0) = pTemp->value;
            *(pRetVal + 1) = i;
            break;
        }
    }
    freeAll(pHashTable);

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int target;
        int returnSize;
    } testCase[] = {{{2, 7, 11, 15}, 4, 9, 0}, {{3, 2, 4}, 3, 6, 0}, {{3, 3}, 2, 6, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,7,11,15], target = 9
     *  Output: [0,1]
     *
     *  Input: nums = [3,2,4], target = 6
     *  Output: [1,2]
     *
     *  Input: nums = [3,3], target = 6
     *  Output: [0,1]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        pAnswer = twoSum(testCase[i].nums, testCase[i].numsSize, testCase[i].target, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
