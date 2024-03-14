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
int numSubarraysWithSum(int *nums, int numsSize, int goal) {
    int retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;

    int key;
    int sum = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &sum, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTemp->key = sum;
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value += 1;
        }

        sum += nums[i];

        key = sum - goal;
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            retVal += pTemp->value;
        }
    }

exit:
    freeAll(pHashTable);
    pHashTable = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int goal;
    } testCase[] = {{{1, 0, 1, 0, 1}, 5, 2}, {{0, 0, 0, 0, 0}, 5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,0,1,0,1], goal = 2
     *  Output: 4
     *
     *  Input: nums = [0,0,0,0,0], goal = 0
     *  Output: 15
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], goal = %d\n", testCase[i].goal);

        answer = numSubarraysWithSum(testCase[i].nums, testCase[i].numsSize, testCase[i].goal);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
