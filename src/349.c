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
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    //
    int mallocSize = (nums1Size > nums2Size) ? nums1Size : nums2Size;
    pRetVal = (int*)malloc(mallocSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (mallocSize * sizeof(int)));

    //
    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int num;
    int i;
    for (i = 0; i < nums1Size; ++i) {
        num = nums1[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &num, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return pRetVal;
            }
            pTemp->key = num;
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        }
    }
    //
    for (i = 0; i < nums2Size; ++i) {
        num = nums2[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &num, pTemp);
        if (pTemp == NULL) {
            continue;
        }

        if (pTemp->value == 1) {
            pRetVal[(*returnSize)++] = num;
            pTemp->value = 0;
        }
    }

    //
    freeAll(pHashTable);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
        int returnSize;
    } testCase[] = {{{1, 2, 2, 1}, 4, {2, 2}, 2, 0}, {{4, 9, 5}, 3, {9, 4, 9, 8, 4}, 5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums1 = [1,2,2,1], nums2 = [2,2]
     *  Output: [2]
     *
     *  Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
     *  Output: [9,4]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums1 = [");
        for (j = 0; j < testCase[i].nums1Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums1[j]);
        }
        printf("], nums2 = [");
        for (j = 0; j < testCase[i].nums2Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums2[j]);
        }
        printf("]\n");

        pAnswer = intersection(testCase[i].nums1, testCase[i].nums1Size, testCase[i].nums2, testCase[i].nums2Size,
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