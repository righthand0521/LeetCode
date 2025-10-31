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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getSneakyNumbers(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)calloc(2, sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int key;
    for (int i = 0; i < numsSize; ++i) {
        key = nums[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            pTemp->value++;
            if (pTemp->value == 2) {
                pRetVal[(*returnSize)++] = nums[i];
                if ((*returnSize) == 2) {
                    break;
                }
            }
            continue;
        }

        pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            break;
        }
        pTemp->key = nums[i];
        pTemp->value = 1;
        HASH_ADD_INT(pHashTable, key, pTemp);
    }

    //
    freeAll(pHashTable);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{0, 1, 1, 0}, 4, 0}, {{0, 3, 2, 1, 3, 2}, 6, 0}, {{7, 1, 5, 4, 3, 4, 6, 0, 9, 5, 8, 2}, 12, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,1,1,0]
     *  Output: [0,1]
     *
     *  Input: nums = [0,3,2,1,3,2]
     *  Output: [2,3]
     *
     *  Input: nums = [7,1,5,4,3,4,6,0,9,5,8,2]
     *  Output: [4,5]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = getSneakyNumbers(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
