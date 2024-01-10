#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashStruct {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    bool retVal = false;

    struct hashStruct* pHashTable = NULL;
    struct hashStruct* pTemp;
    int i;
    for (i = 0; i < numsSize; ++i) {
        pTemp = NULL;

        HASH_FIND_INT(pHashTable, &nums[i], pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = nums[i];
            pTemp->value = i;
            HASH_ADD_INT(pHashTable, key, pTemp);
            continue;
        }

        if ((i - pTemp->value) <= k) {
            retVal = true;
            break;
        }

        pTemp->value = i;
    }
    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 2, 3, 1}, 4, 3}, {{1, 0, 1, 1}, 4, 1}, {{1, 2, 3, 1, 2, 3}, 6, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example:
     *  Input: nums = [1,2,3,1], k = 3
     *  Output: true
     *
     *  Input: nums = [1,0,1,1], k = 1
     *  Output: true
     *
     *  Input: nums = [1,2,3,1,2,3], k = 2
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = containsNearbyDuplicate(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
