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
int maxSubarrayLength(int *nums, int numsSize, int k) {
    int retVal = 0;

    struct hashTable *pFrequency = NULL;
    struct hashTable *pTempStart, *pTempEnd;
    int startKey, endKey;
    int start = -1, end = 0;
    for (end = 0; end < numsSize; ++end) {
        endKey = nums[end];
        pTempEnd = NULL;
        HASH_FIND_INT(pFrequency, &endKey, pTempEnd);
        if (pTempEnd == NULL) {
            pTempEnd = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTempEnd == NULL) {
                perror("malloc");
                goto exit;
            }
            pTempEnd->key = endKey;
            pTempEnd->value = 1;
            HASH_ADD_INT(pFrequency, key, pTempEnd);
        } else {
            pTempEnd->value += 1;
        }

        while (pTempEnd->value > k) {
            start++;

            startKey = nums[start];
            pTempStart = NULL;
            HASH_FIND_INT(pFrequency, &startKey, pTempStart);
            pTempStart->value -= 1;
        }

        retVal = fmax(retVal, (end - start));
    }

exit:
    freeAll(pFrequency);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 2, 3, 1, 2, 3, 1, 2}, 8, 2},
                    {{1, 2, 1, 2, 1, 2, 1, 2}, 8, 1},
                    {{5, 5, 5, 5, 5, 5, 5}, 7, 4},
                    {{1, 4, 4, 3}, 4, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,1,2,3,1,2], k = 2
     *  Output: 6
     *
     *  Input: nums = [1,2,1,2,1,2,1,2], k = 1
     *  Output: 2
     *
     *  Input: nums = [5,5,5,5,5,5,5], k = 4
     *  Output: 4
     *
     *  Input: nums = [1,4,4,3], k = 1
     *  Output: 2
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maxSubarrayLength(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
