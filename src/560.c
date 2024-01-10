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
        HASH_DEL(pFree, current);
        free(current);
    }
}
int subarraySum(int *nums, int numsSize, int k) {
    int retVal = 0;

    struct hashTable *pPrefixSumMap = NULL;
    struct hashTable *pTmp = NULL;
    pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTmp == NULL) {
        perror("malloc");
        freeAll(pPrefixSumMap);
        return retVal;
    }
    pTmp->key = 0;
    pTmp->value = 1;
    HASH_ADD_INT(pPrefixSumMap, key, pTmp);

    int prefixSum = 0;
    int num;
    int i;
    for (i = 0; i < numsSize; ++i) {
        prefixSum += nums[i];

        num = prefixSum - k;
        pTmp = NULL;
        HASH_FIND_INT(pPrefixSumMap, &num, pTmp);
        if (pTmp != NULL) {
            retVal += pTmp->value;
        }

        num = prefixSum;
        pTmp = NULL;
        HASH_FIND_INT(pPrefixSumMap, &num, pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pPrefixSumMap);
                return retVal;
            }
            pTmp->key = num;
            pTmp->value = 1;
            HASH_ADD_INT(pPrefixSumMap, key, pTmp);
        } else {
            pTmp->value += 1;
        }
    }
    freeAll(pPrefixSumMap);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (2 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 1, 1}, 3, 2}, {{1, 2, 3}, 3, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,1], k = 2
     *  Output: 2
     *
     *  Input: nums = [1,2,3], k = 3
     *  Output: 2
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = subarraySum(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
