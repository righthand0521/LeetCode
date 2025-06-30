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
int findLHS(int *nums, int numsSize) {
    int retVal = 0;

    struct hashTable *frequency = NULL;
    struct hashTable *entry;
    for (int i = 0; i < numsSize; i++) {
        entry = NULL;
        HASH_FIND_INT(frequency, &nums[i], entry);
        if (entry == NULL) {
            entry = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (entry == NULL) {
                perror("malloc");
                freeAll(frequency);
                frequency = NULL;
                return retVal;
            }
            entry->key = nums[i];
            entry->value = 1;
            HASH_ADD_INT(frequency, key, entry);
        } else {
            entry->value++;
        }
    }

    int key;
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, frequency, current, tmp) {
        key = current->key + 1;
        entry = NULL;
        HASH_FIND_INT(frequency, &key, entry);
        if (entry != NULL) {
            retVal = fmax(retVal, current->value + entry->value);
        }
    }

    //
    freeAll(frequency);
    frequency = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (2 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3, 2, 2, 5, 2, 3, 7}, 8}, {{1, 2, 3, 4}, 4}, {{1, 1, 1, 1}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,2,2,5,2,3,7]
     *  Output: 5
     *
     *  Input: nums = [1,2,3,4]
     *  Output: 2
     *
     *  Input: nums = [1,1,1,1]
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

        answer = findLHS(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
