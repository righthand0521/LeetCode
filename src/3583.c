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
#define MODULO (int)(1e9 + 7)
int specialTriplets(int* nums, int numsSize) {
    int retVal = 0;

    struct hashTable* pTemp;
    int key;

    struct hashTable* numCnt = NULL;
    for (int i = 0; i < numsSize; i++) {
        key = nums[i];

        pTemp = NULL;
        HASH_FIND_INT(numCnt, &key, pTemp);
        if (pTemp != NULL) {
            pTemp->value += 1;
            continue;
        }
        pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            freeAll(numCnt);
            return retVal;
        }
        pTemp->key = key;
        pTemp->value = 1;
        HASH_ADD_INT(numCnt, key, pTemp);
    }

    struct hashTable* numPartialCnt = NULL;
    int target;
    long long answer = 0, lCnt, rCnt;
    for (int i = 0; i < numsSize; i++) {
        key = nums[i];
        target = key * 2;

        lCnt = 0;
        pTemp = NULL;
        HASH_FIND_INT(numPartialCnt, &target, pTemp);
        if (pTemp != NULL) {
            lCnt = pTemp->value;
        }

        pTemp = NULL;
        HASH_FIND_INT(numPartialCnt, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(numCnt);
                freeAll(numPartialCnt);
                return retVal;
            }
            pTemp->key = key;
            pTemp->value = 1;
            HASH_ADD_INT(numPartialCnt, key, pTemp);
        } else {
            pTemp->value += 1;
        }

        rCnt = 0;
        pTemp = NULL;
        HASH_FIND_INT(numCnt, &target, pTemp);
        if (pTemp != NULL) {
            rCnt = pTemp->value;
        }
        pTemp = NULL;
        HASH_FIND_INT(numPartialCnt, &target, pTemp);
        if (pTemp != NULL) {
            rCnt -= pTemp->value;
        }

        answer = (answer + lCnt * rCnt) % MODULO;
    }
    retVal = (int)answer;

    //
    freeAll(numCnt);
    freeAll(numPartialCnt);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{6, 3, 6}, 3}, {{0, 1, 0, 0}, 4}, {{8, 4, 2, 8, 4}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [6,3,6]
     *  Output: 1
     *
     *  Input: nums = [0,1,0,0]
     *  Output: 1
     *
     *  Input: nums = [8,4,2,8,4]
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

        answer = specialTriplets(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
