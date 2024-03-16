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
int findMaxLength(int *nums, int numsSize) {
    int retVal = 0;

    int sum = 0;
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp = NULL;
    pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        goto exit;
    }
    pTemp->key = sum;
    pTemp->value = -1;
    HASH_ADD_INT(pHashTable, key, pTemp);

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 1) {
            sum++;
        } else if (nums[i] == 0) {
            sum--;
        }

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &sum, pTemp);
        if (pTemp != NULL) {
            retVal = fmax(retVal, i - pTemp->value);
        } else {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTemp->key = sum;
            pTemp->value = i;
            HASH_ADD_INT(pHashTable, key, pTemp);
        }
    }

exit:
    freeAll(pHashTable);
    pHashTable = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{0, 1}, 2}, {{0, 1, 0}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,1]
     *  Output: 2
     *
     *  Input: nums = [0,1,0]
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = findMaxLength(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
