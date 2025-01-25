#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

// https://leetcode.cn/problems/make-lexicographically-smallest-array-by-swapping-elements/solutions/2545365/c-by-awesome-ardinghelli-jqrs/
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
int compareStruct(const void *a, const void *b) {
    int pa = ((struct hashTable *)a)->value;
    int pb = ((struct hashTable *)b)->value;

    // ascending order
    return (pa > pb);
}
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *lexicographicallySmallestArray(int *nums, int numsSize, int limit, int *returnSize) {
    int *pRetVal = NULL;

    //
    (*returnSize) = 0;

    //
    pRetVal = (int *)calloc(numsSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    (*returnSize) = numsSize;

    //
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTmp = NULL;
    for (int i = 0; i < numsSize; i++) {
        pTmp = NULL;
        pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            freeAll(pHashTable);
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        pTmp->key = i;
        pTmp->value = nums[i];
        HASH_ADD_INT(pHashTable, key, pTmp);
    }
    HASH_SORT(pHashTable, compareStruct);

    //
    int groupSize = (1e5);  // 1 <= nums.length <= 10^5
    int groupIndex[groupSize];
    memset(groupIndex, 0, sizeof(groupIndex));
    int group[groupSize];
    memset(group, 0, sizeof(group));
    int FirstNum = nums[0];
    int key = 0;
    struct hashTable *pCurrent = NULL;
    pTmp = NULL;
    HASH_ITER(hh, pHashTable, pCurrent, pTmp) {
        if (pCurrent->value - FirstNum > limit) {
            qsort(groupIndex, key, sizeof(groupIndex[0]), compareInteger);
            for (int i = 0; i < key; i++) {
                pRetVal[groupIndex[i]] = group[i];
            }
            key = 0;
        }
        group[key] = pCurrent->value;
        groupIndex[key++] = pCurrent->key;
        FirstNum = pCurrent->value;
    }

    //
    qsort(groupIndex, key, sizeof(groupIndex[0]), compareInteger);
    for (int i = 0; i < key; i++) {
        pRetVal[groupIndex[i]] = group[i];
    }

    //
    freeAll(pHashTable);

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int limit;
        int returnSize;
    } testCase[] = {{{1, 5, 3, 9, 8}, 5, 2, 0}, {{1, 7, 6, 18, 2, 1}, 6, 3, 0}, {{1, 7, 28, 19, 10}, 5, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,5,3,9,8], limit = 2
     *  Output: [1,3,5,8,9]
     *
     *  Input: nums = [1,7,6,18,2,1], limit = 3
     *  Output: [1,6,7,18,1,2]
     *
     *  Input: nums = [1,7,28,19,10], limit = 3
     *  Output: [1,7,28,19,10]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], limit = %d\n", testCase[i].limit);

        pAnswer = lexicographicallySmallestArray(testCase[i].nums, testCase[i].numsSize, testCase[i].limit,
                                                 &testCase[i].returnSize);
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
