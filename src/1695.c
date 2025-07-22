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
int maximumUniqueSubarray(int *nums, int numsSize) {
    int retVal = 0;

    int prefixsum[numsSize + 1];
    memset(prefixsum, 0, sizeof(prefixsum));

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int previous = 0;
    int num;
    for (int i = 0; i < numsSize; ++i) {
        prefixsum[i + 1] = prefixsum[i] + nums[i];

        num = nums[i];
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &num, pTemp);
        if (pTemp == NULL) {
            previous = fmax(previous, 0);

            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                break;
            }
            pTemp->key = nums[i];
            pTemp->value = i + 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            previous = fmax(previous, pTemp->value);
            pTemp->value = i + 1;
        }
        retVal = fmax(retVal, prefixsum[i + 1] - prefixsum[previous]);
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
    } testCase[] = {{{4, 2, 4, 5, 6}, 5}, {{5, 2, 1, 2, 5, 2, 1, 2, 5}, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,2,4,5,6]
     *  Output: 17
     *
     *  Input: nums = [5,2,1,2,5,2,1,2,5]
     *  Output: 8
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maximumUniqueSubarray(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
