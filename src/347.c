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
        HASH_DEL(pFree, current);
        free(current);
    }
}
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // descending order
    if (p1[1] == p2[1]) {
        return (p1[0] > p2[0]);
    }
    return (p1[1] < p2[1]);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    //
    int hashTableSize = 0;
    struct hashTable* pMap = NULL;
    struct hashTable* pTmp;
    int i;
    for (i = 0; i < numsSize; ++i) {
        pTmp = NULL;
        HASH_FIND_INT(pMap, &nums[i], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pMap);
                return pRetVal;
            }
            pTmp->key = nums[i];
            pTmp->value = 1;
            HASH_ADD_INT(pMap, key, pTmp);
            ++hashTableSize;
        } else {
            pTmp->value += 1;
        }
    }

    //
    int sortCounter[hashTableSize][2];
    memset(sortCounter, 0, sizeof(sortCounter));
    i = 0;
    pTmp = NULL;
    struct hashTable* pCurrent = NULL;
    HASH_ITER(hh, pMap, pCurrent, pTmp) {
        sortCounter[i][0] = pCurrent->key;
        sortCounter[i][1] = pCurrent->value;
        ++i;

        HASH_DEL(pMap, pCurrent);
        free(pCurrent);
    }
    qsort(sortCounter, hashTableSize, sizeof(sortCounter[0]), compareIntArray);

    //
    (*returnSize) = k;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = sortCounter[i][0];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
        int returnSize;
    } testCase[] = {{{1, 1, 1, 2, 2, 3}, 6, 2, 0}, {{1}, 1, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,1,2,2,3], k = 2
     *  Output: [1,2]
     *
     *  Input: nums = [1], k = 1
     *  Output: [1]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pAnswer = topKFrequent(testCase[i].nums, testCase[i].numsSize, testCase[i].k, &testCase[i].returnSize);
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
