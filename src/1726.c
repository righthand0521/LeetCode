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
int tupleSameProduct(int *nums, int numsSize) {
    int retVal = 0;

    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int productValue;
    for (int firstIndex = 0; firstIndex < numsSize; firstIndex++) {
        for (int secondIndex = firstIndex + 1; secondIndex < numsSize; secondIndex++) {
            productValue = nums[firstIndex] * nums[secondIndex];

            pTemp = NULL;
            HASH_FIND_INT(pHashTable, &productValue, pTemp);
            if (pTemp == NULL) {
                pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
                if (pTemp == NULL) {
                    perror("malloc");
                    freeAll(pHashTable);
                    return retVal;
                }
                pTemp->key = productValue;
                pTemp->value = 1;
                HASH_ADD_INT(pHashTable, key, pTemp);
            } else {
                pTemp->value += 1;
            }
        }
    }

    struct hashTable *pCurrent;
    HASH_ITER(hh, pHashTable, pCurrent, pTemp) {
        retVal += 8 * ((pHashTable->value - 1) * pHashTable->value / 2);  // each pair can form 8 tuples
        HASH_DEL(pHashTable, pCurrent);
        free(pCurrent);
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 3, 4, 6}, 4}, {{1, 2, 4, 5, 10}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,3,4,6]
     *  Output: 8
     *
     *  Input: nums = [1,2,4,5,10]
     *  Output: 16
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = tupleSameProduct(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
