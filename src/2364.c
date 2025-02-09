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
long long countBadPairs(int *nums, int numsSize) {
    long long retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int diff, goodPairsCount;
    for (int pos = 0; pos < numsSize; pos++) {
        diff = pos - nums[pos];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &diff, pTemp);
        if (pTemp == NULL) {
            goodPairsCount = 0;  // Count of previous positions with same difference

            // Update count of positions with this difference
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = diff;
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            goodPairsCount = pTemp->value;      // Count of previous positions with same difference
            pTemp->value = goodPairsCount + 1;  // Update count of positions with this difference
        }

        retVal += (pos - goodPairsCount);  // Total possible pairs minus good pairs = bad pairs
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
    } testCase[] = {{{4, 1, 3, 3}, 4}, {{1, 2, 3, 4, 5}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,1,3,3]
     *  Output: 5
     *
     *  Input: nums = [1,2,3,4,5]
     *  Output: 0
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = countBadPairs(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
