#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MODULO (int)(1e9 + 7)
struct hashTable {
    int index;
    int count;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
int reverseInteger(int num) {
    int retVal = 0;

    while (num > 0) {
        retVal = 10 * retVal + num % 10;
        num /= 10;
    }
    return retVal;
}
int countNicePairs(int *nums, int numsSize) {
    int retVal = 0;

    /* nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
     * =>  nums[i] - rev(nums[i]) == nums[j] - rev(nums[j])
     */
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTmp;
    int index;
    int i;
    for (i = 0; i < numsSize; ++i) {
        index = nums[i] - reverseInteger(nums[i]);

        pTmp = NULL;
        HASH_FIND_INT(pHashTable, &index, pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTmp->index = index;
            pTmp->count = 1;
            HASH_ADD_INT(pHashTable, index, pTmp);
        } else {
            retVal = (retVal + pTmp->count) % MODULO;
            pTmp->count++;
        }
    }
    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_NUMSSIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_NUMSSIZE];
        int numsSize;
    } testCase[] = {{{42, 11, 1, 97}, 4}, {{13, 10, 35, 24, 76}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [42,11,1,97]
     *  Output: 2
     *
     *  Input: nums = [13,10,35,24,76]
     *  Output: 4
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = countNicePairs(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
