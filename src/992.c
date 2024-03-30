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
int atMostDifferent(int* nums, int numsSize, int k) {
    int retVal = 0;

    int pHashTableSize = 0;
    struct hashTable* pHashTable = NULL;
    struct hashTable* pTemp;
    int key;
    int left = 0;
    int right = 0;
    for (right = 0; right < numsSize; ++right) {
        key = nums[right];
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                break;
            }
            pTemp->key = key;
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value += 1;
        }

        pHashTableSize = HASH_COUNT(pHashTable);
        while (pHashTableSize > k) {
            key = nums[left];
            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &key, pTemp);
            if (pTemp != NULL) {
                pTemp->value -= 1;
                if (pTemp->value == 0) {
                    HASH_DEL(pHashTable, pTemp);
                    free(pTemp);
                    pHashTableSize = HASH_COUNT(pHashTable);
                }
            }
            ++left;
        }

        retVal += (right - left);
    }
    freeAll(pHashTable);

    return retVal;
}
int subarraysWithKDistinct(int* nums, int numsSize, int k) {
    int retVal = 0;

    // https://leetcode.com/problems/subarrays-with-k-different-integers/solutions/523136/JavaC++Python-Sliding-Window/
    retVal = atMostDifferent(nums, numsSize, k) - atMostDifferent(nums, numsSize, k - 1);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 2, 1, 2, 3}, 5, 2}, {{1, 2, 1, 3, 4}, 5, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,1,2,3], k = 2
     *  Output: 7
     *
     *  Input: nums = [1,2,1,3,4], k = 3
     *  Output: 3
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = subarraysWithKDistinct(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
