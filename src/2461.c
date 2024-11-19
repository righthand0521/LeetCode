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
long long maximumSubarraySum(int *nums, int numsSize, int k) {
    long long retVal = 0;

    struct hashTable *numToIndex = NULL;
    struct hashTable *pTemp;

    int currNum, lastOccurrence;
    long long currentSum = 0;
    int begin = 0;
    int end = 0;
    while (end < numsSize) {
        currNum = nums[end];

        pTemp = NULL;
        HASH_FIND_INT(numToIndex, &currNum, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(numToIndex);
                return retVal;
            }
            pTemp->key = currNum;
            pTemp->value = -1;
            HASH_ADD_INT(numToIndex, key, pTemp);
        }
        lastOccurrence = pTemp->value;

        // if current window already has number or if window is too big, adjust window
        while ((begin <= lastOccurrence) || (end - begin + 1 > k)) {
            currentSum -= nums[begin];
            begin++;
        }

        pTemp = NULL;
        pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            freeAll(numToIndex);
            return retVal;
        }
        pTemp->key = currNum;
        pTemp->value = end;
        HASH_ADD_INT(numToIndex, key, pTemp);

        currentSum += nums[end];
        if (end - begin + 1 == k) {
            retVal = fmax(retVal, currentSum);
        }

        end++;
    }

    //
    freeAll(numToIndex);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 5, 4, 2, 9, 9, 9}, 7, 3}, {{4, 4, 4}, 3, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,5,4,2,9,9,9], k = 3
     *  Output: 15
     *
     *  Input: nums = [4,4,4], k = 3
     *  Output: 0
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maximumSubarraySum(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
