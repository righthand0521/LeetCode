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
int minSubarray(int *nums, int numsSize, int p) {
    int retVal = 0;

    // Step 1: Calculate total sum and target remainder
    int totalSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        totalSum = (totalSum + nums[i]) % p;
    }
    int target = totalSum % p;
    if (target == 0) {  // The array is already divisible by p
        return retVal;
    }

    // Step 2: Use a hash map to track prefix sum mod p
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp = NULL;
    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        return retVal;
    }
    pTemp->key = 0;
    pTemp->value = -1;
    HASH_ADD_INT(pHashTable, key, pTemp);

    // Step 3: Iterate over the array
    retVal = numsSize;
    int needed;
    int currentSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        currentSum = (currentSum + nums[i]) % p;

        needed = (currentSum - target + p) % p;  // Calculate what we need to remove
        // If we have seen the needed remainder, we can consider this subarray
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &needed, pTemp);
        if (pTemp != NULL) {
            retVal = fmin(retVal, i - pTemp->value);
        }

        // Store the current remainder and index
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &currentSum, pTemp);
        if (pTemp == NULL) {
            pTemp = NULL;
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = currentSum;
            pTemp->value = i;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value = i;
        }
    }

    if (retVal == numsSize) {
        retVal = -1;
    }

    //
    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int p;
    } testCase[] = {{{3, 1, 4, 2}, 4, 6}, {{6, 3, 5, 2}, 4, 9}, {{1, 2, 3}, 3, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,1,4,2], p = 6
     *  Output: 1
     *
     *  Input: nums = [6,3,5,2], p = 9
     *  Output: 2
     *
     *  Input: nums = [1,2,3], p = 3
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], p = %d\n", testCase[i].p);

        answer = minSubarray(testCase[i].nums, testCase[i].numsSize, testCase[i].p);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
