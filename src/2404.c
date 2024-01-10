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
        HASH_DEL(pFree, current);
        free(current);
    }
}
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // descending order
    if (p1[1] == p2[1]) {
        return (p1[0] > p2[0]);
    }
    return (p1[1] < p2[1]);
}
int mostFrequentEven(int* nums, int numsSize) {
    int retVal = -1;

    //
    int hashTableSize = 0;
    struct hashTable* pMap = NULL;
    struct hashTable* pTmp;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] % 2 != 0) {
            continue;
        }

        pTmp = NULL;
        HASH_FIND_INT(pMap, &nums[i], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pMap);
                return retVal;
            }
            pTmp->key = nums[i];
            pTmp->value = 1;
            HASH_ADD_INT(pMap, key, pTmp);
            ++hashTableSize;
        } else {
            pTmp->value += 1;
        }
    }
    if (hashTableSize == 0) {
        return retVal;
    }

    //
    int sortHashTable[hashTableSize][2];
    memset(sortHashTable, 0, sizeof(sortHashTable));
    i = 0;
    pTmp = NULL;
    struct hashTable* pCurrent = NULL;
    HASH_ITER(hh, pMap, pCurrent, pTmp) {
        sortHashTable[i][0] = pCurrent->key;
        sortHashTable[i][1] = pCurrent->value;
        ++i;

        HASH_DEL(pMap, pCurrent);
        free(pCurrent);
    }
    qsort(sortHashTable, hashTableSize, sizeof(sortHashTable[0]), compareIntArray);
    retVal = sortHashTable[0][0];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{0, 1, 2, 2, 4, 4, 1}, 7}, {{4, 4, 4, 9, 2, 4}, 6}, {{29, 47, 21, 41, 13, 37, 25, 7}, 8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,1,2,2,4,4,1]
     *  Output: 2
     *
     *  Input: nums = [4,4,4,9,2,4]
     *  Output: 4
     *
     *  Input: nums = [29,47,21,41,13,37,25,7]
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = mostFrequentEven(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
