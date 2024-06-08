#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
bool checkSubarraySum(int* nums, int numsSize, int k) {
    bool retVal = false;

    struct hashTable* pMmodSeen = NULL;
    struct hashTable* pTmp = NULL;
    pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (pTmp == NULL) {
        goto exit;
    }
    pTmp->key = 0;
    pTmp->value = -1;
    HASH_ADD_INT(pMmodSeen, key, pTmp);

    int prefixMod = 0;
    int i;
    for (i = 0; i < numsSize; i++) {
        prefixMod = (prefixMod + nums[i]) % k;

        pTmp = NULL;
        HASH_FIND_INT(pMmodSeen, &prefixMod, pTmp);
        if (pTmp != NULL) {  // ensures that the size of subarray is atleast 2
            if (i - pTmp->value > 1) {
                retVal = true;
                break;
            }
        } else {  // mark the value of prefixMod with the current index.
            pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                goto exit;
            }
            pTmp->key = prefixMod;
            pTmp->value = i;
            HASH_ADD_INT(pMmodSeen, key, pTmp);
        }
    }

exit:
    //
    freeAll(pMmodSeen);
    pMmodSeen = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{23, 2, 4, 6, 7}, 5, 6}, {{23, 2, 6, 4, 7}, 5, 6}, {{23, 2, 6, 4, 7}, 5, 13}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example:
     *  Input: nums = [23,2,4,6,7], k = 6
     *  Output: true
     *
     *  Input: nums = [23,2,6,4,7], k = 6
     *  Output: true
     *
     *  Input: nums = [23,2,6,4,7], k = 13
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

        answer = checkSubarraySum(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
