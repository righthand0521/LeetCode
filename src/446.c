#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define HASH_FIND_LONG(head, findint, out) HASH_FIND(hh, head, findint, sizeof(long), out)
#define HASH_ADD_LONG(head, intfield, add) HASH_ADD(hh, head, intfield, sizeof(long), add)
struct HashTable {
    long key;
    int val;
    UT_hash_handle hh;
};
void freeAll(struct HashTable* pFree) {
    struct HashTable* current;
    struct HashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->val);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int numberOfArithmeticSlices(int* nums, int numsSize) {
    int retVal = 0;

    struct HashTable* dp[numsSize];
    memset(dp, 0, sizeof(dp));

    long long diff;
    struct HashTable* pTmp;
    int count;
    int i, j;
    for (i = 0; i < numsSize; ++i) {
        for (j = 0; j < i; ++j) {
            diff = (long long)nums[i] - (long long)nums[j];

            pTmp = NULL;
            HASH_FIND_LONG(dp[j], &diff, pTmp);
            count = ((pTmp == NULL) ? 0 : pTmp->val);
            retVal += count;

            pTmp = NULL;
            HASH_FIND_LONG(dp[i], &diff, pTmp);
            if (pTmp == NULL) {
                pTmp = (struct HashTable*)malloc(sizeof(struct HashTable));
                if (pTmp == NULL) {
                    perror("malloc");
                    for (i = 0; i < numsSize; ++i) {
                        freeAll(dp[i]);
                        dp[i] = NULL;
                    }
                    return retVal;
                }
                pTmp->key = diff;
                pTmp->val = count + 1;
                HASH_ADD_LONG(dp[i], key, pTmp);
            } else {
                pTmp->val += (count + 1);
            }
        }
    }
    for (i = 0; i < numsSize; ++i) {
        freeAll(dp[i]);
        dp[i] = NULL;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 4, 6, 8, 10}, 5}, {{7, 7, 7, 7, 7}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,4,6,8,10]
     *  Output: 7
     *
     *  Input: nums = [7,7,7,7,7]
     *  Output: 16
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = numberOfArithmeticSlices(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
