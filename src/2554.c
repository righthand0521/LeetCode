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
int maxCount(int *banned, int bannedSize, int n, int maxSum) {
    int retVal = 0;

    // Store banned numbers in an unordered_set
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    int key;
    int i;
    for (i = 0; i < bannedSize; ++i) {
        key = banned[i];

        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pHashTable);
                return retVal;
            }
            pTemp->key = key;
            pTemp->value = 1;
            HASH_ADD_INT(pHashTable, key, pTemp);
        } else {
            pTemp->value += 1;
        }
    }

    for (i = 1; i <= n; ++i) {
        // Skip banned numbers
        key = i;
        pTemp = NULL;
        HASH_FIND_INT(pHashTable, &key, pTemp);
        if (pTemp != NULL) {
            continue;
        }

        // Return if adding current number exceeds maxSum
        if (maxSum - i < 0) {
            break;
        }

        // Include current number
        maxSum -= i;
        retVal++;
    }

    //
    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int banned[MAX_SIZE];
        int bannedSize;
        int n;
        int maxSum;
    } testCase[] = {{{1, 6, 5}, 3, 5, 6}, {{1, 2, 3, 4, 5, 6, 7}, 7, 8, 1}, {{11}, 1, 7, 50}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: banned = [1,6,5], n = 5, maxSum = 6
     *  Output: 2
     *
     *  Input: banned = [1,2,3,4,5,6,7], n = 8, maxSum = 1
     *  Output: 0
     *
     *  Input: banned = [11], n = 7, maxSum = 50
     *  Output: 7
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: banned = [");
        for (j = 0; j < testCase[i].bannedSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].banned[j]);
        }
        printf("], n = %d, maxSum = %d\n", testCase[i].n, testCase[i].maxSum);

        answer = maxCount(testCase[i].banned, testCase[i].bannedSize, testCase[i].n, testCase[i].maxSum);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
