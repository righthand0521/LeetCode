#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
struct hashTable *pFrequency = NULL;
int hashGetItem(struct hashTable **obj, int key) {
    int retVal = 0;

    struct hashTable *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    if (pEntry != NULL) {
        retVal = pEntry->value;
    }

    return retVal;
}
void hashFree(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
static inline int compareIntArray(const void *a1, const void *a2) {
    int p1 = *(int *)a1;
    int p2 = *(int *)a2;

    int pFrequency1 = hashGetItem(&pFrequency, p1);
    int pFrequency2 = hashGetItem(&pFrequency, p2);
    if (pFrequency1 == pFrequency2) {
        // descending order
        return (p1 < p2);
    }

    // ascending order
    return (pFrequency1 > pFrequency2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *frequencySort(int *nums, int numsSize, int *returnSize) {
    int *pRetVal = 0;

    //
    (*returnSize) = 0;

    //
    pFrequency = NULL;
    struct hashTable *pTemp;
    int key;
    int i;
    for (i = 0; i < numsSize; i++) {
        key = nums[i];
        pTemp = NULL;
        HASH_FIND_INT(pFrequency, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                hashFree(pFrequency);
                return pRetVal;
            }
            pTemp->key = key;
            pTemp->value = 1;
            HASH_ADD_INT(pFrequency, key, pTemp);
        } else {
            pTemp->value += 1;
        }
    }

    //
    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        hashFree(pFrequency);
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));
    memcpy(pRetVal, nums, (numsSize * sizeof(int)));
    (*returnSize) = numsSize;

    //
    qsort(pRetVal, (*returnSize), sizeof(int), compareIntArray);

    //
    hashFree(pFrequency);

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, 1, 2, 2, 2, 3}, 5, 0}, {{2, 3, 1, 3, 2}, 5, 0}, {{-1, 1, -6, 4, 5, -6, 1, 4, 1}, 9, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,2,2,2,3]
     *  Output: [3,1,1,2,2,2]
     *
     *  Input: nums = [2,3,1,3,2]
     *  Output: [1,3,3,2,2]
     *
     *  Input: nums = [-1,1,-6,4,5,-6,1,4,1]
     *  Output: [5,-1,4,4,-6,-6,1,1,1]
     */

    int *pAnswer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = frequencySort(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", *(pAnswer + j));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
