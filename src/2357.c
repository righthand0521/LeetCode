#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashStruct {
    int key;
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
int minimumOperations(int* nums, int numsSize) {
    int retVal = 0;

    struct hashStruct* pHashTable = NULL;
    struct hashStruct* pTemp;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {  // Each element in nums is already 0 so no operations are needed.
            continue;
        }

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &nums[i], pTemp);
        if (pTemp == NULL) {
            ++retVal;

            pTemp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = nums[i];
            HASH_ADD_INT(pHashTable, key, pTemp);
        }
    }
    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 5, 0, 3, 5}, 5}, {{0}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example:
     *  Input: nums = [1,5,0,3,5]
     *  Output: 3
     *
     *  Input: nums = [0]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minimumOperations(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
