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
int longestSubsequence(int *arr, int arrSize, int difference) {
    int retVal = 0;

    /* Input : arr = [1, 5, 7, 8, 5, 3, 4, 2, 1], difference = -2
     *  1 dp{1 : 1 }
     *  5 dp{1 : 1, 5 : 1 }
     *  7 dp{1 : 1, 5 : 1, 7 : 1 }
     *  8 dp{1 : 1, 5 : 1, 7 : 1, 8 : 1 }
     *  5 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1 }
     *  3 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3 }
     *  4 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1 }
     *  2 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1, 2 : 2 }
     *  1 dp{1 : 1, 5 : 2, 7 : 1, 8 : 1, 3 : 3, 4 : 1, 2 : 2, 1 : 4 }
     */
    struct hashTable *pDp = NULL;
    struct hashTable *pTmp;
    int key, value;
    int i;
    for (i = 0; i < arrSize; ++i) {
        key = arr[i] - difference;
        value = 0;

        pTmp = NULL;
        HASH_FIND_INT(pDp, &key, pTmp);
        if (pTmp != NULL) {
            value = pTmp->value;
        }

        key = arr[i];
        pTmp = NULL;
        HASH_FIND_INT(pDp, &key, pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pDp);
                return retVal;
            }
            pTmp->key = key;
            pTmp->value = value + 1;
            HASH_ADD_INT(pDp, key, pTmp);
        } else {
            pTmp->value = value + 1;
        }

        retVal = fmax(retVal, value + 1);
    }
    freeAll(pDp);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int difference;
    } testCase[] = {{{1, 2, 3, 4}, 4, 1}, {{1, 3, 5, 7}, 4, 1}, {{1, 5, 7, 8, 5, 3, 4, 2, 1}, 9, -2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [1,2,3,4], difference = 1
     *  Output: 4
     *
     *  Input: arr = [1,3,5,7], difference = 1
     *  Output: 1
     *
     *  Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].arr[j]);
        }
        printf("], difference = %d\n", testCase[i].difference);

        answer = longestSubsequence(testCase[i].arr, testCase[i].arrSize, testCase[i].difference);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
