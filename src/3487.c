#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int maxSum(int *nums, int numsSize) {
    int retVal = 0;

    int maxNum = nums[0];
    int sumOfPositiveNumsSet = 0;
    struct hashTable *pPositiveNumsSet = NULL;
    struct hashTable *pTemp;
    int key;
    for (int i = 0; i < numsSize; i++) {
        maxNum = fmax(maxNum, nums[i]);

        if (nums[i] <= 0) {
            continue;
        }

        key = nums[i];
        pTemp = NULL;
        HASH_FIND_INT(pPositiveNumsSet, &key, pTemp);
        if (pTemp != NULL) {
            continue;
        }
        pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            goto exit;
        }
        pTemp->key = key;
        HASH_ADD_INT(pPositiveNumsSet, key, pTemp);
        sumOfPositiveNumsSet += key;
    }

    if (HASH_COUNT(pPositiveNumsSet) == 0) {
        retVal = maxNum;
    } else {
        retVal = sumOfPositiveNumsSet;
    }

exit:
    freeAll(pPositiveNumsSet);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5}, {{1, 1, 0, 1, 1}, 5}, {{1, 2, -1, -2, 1, 0, -1}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,4,5]
     *  Output: 15
     *
     *  Input: nums = [1,1,0,1,1]
     *  Output: 1
     *
     *  Input: nums = [1,2,-1,-2,1,0,-1]
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxSum(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
