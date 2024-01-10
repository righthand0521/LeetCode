#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int freq;
    int first;
    int second;
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* restoreArray(int** adjacentPairs, int adjacentPairsSize, int* adjacentPairsColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    //
    struct hashTable* pGraph = NULL;
    struct hashTable* pCurrent;
    int key, sum;
    int i, j;
    for (i = 0; i < adjacentPairsSize; i++) {
        sum = adjacentPairs[i][0] + adjacentPairs[i][1];

        for (j = 0; j < 2; j++) {
            key = adjacentPairs[i][j];

            pCurrent = NULL;
            HASH_FIND_INT(pGraph, &key, pCurrent);
            if (pCurrent == NULL) {
                pCurrent = (struct hashTable*)malloc(sizeof(struct hashTable));
                if (pCurrent == NULL) {
                    perror("malloc");
                    freeAll(pGraph);
                    return pRetVal;
                }
                pCurrent->key = key;
                pCurrent->freq = 1;
                pCurrent->first = sum - key;
                HASH_ADD_INT(pGraph, key, pCurrent);
            } else {
                pCurrent->freq = 2;
                pCurrent->second = sum - key;
            }
        }
    }

    //
    (*returnSize) = (adjacentPairsSize + 1);
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        freeAll(pGraph);
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    //
    pCurrent = NULL;
    struct hashTable* pTemp;
    HASH_ITER(hh, pGraph, pCurrent, pTemp) {
        if (pCurrent->freq == 1) {
            break;
        }
    }
    pRetVal[0] = pCurrent->key;
    pRetVal[1] = pCurrent->first;

    //
    int prev;
    for (i = 2; i < (*returnSize); i++) {
        key = pRetVal[i - 1];
        prev = pRetVal[i - 2];

        pCurrent = NULL;
        HASH_FIND_INT(pGraph, &key, pCurrent);
        if (pCurrent->first == prev) {
            pRetVal[i] = pCurrent->second;
        } else {
            pRetVal[i] = pCurrent->first;
        }
    }

    //
    freeAll(pGraph);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (int)(1e5)
#define MAX_COLUMN (2)
    struct testCaseType {
        int adjacentPairs[MAX_ROW][MAX_COLUMN];
        int adjacentPairsSize;
        int adjacentPairsColSize[MAX_ROW];
        int returnSize;
    } testCase[] = {{{{2, 1}, {3, 4}, {3, 2}}, 3, {2, 2, 2}, 0},
                    {{{4, -2}, {1, 4}, {-3, 1}}, 3, {2, 2, 2}, 0},
                    {{{100000, -100000}}, 1, {2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: adjacentPairs = [[2,1],[3,4],[3,2]]
     *  Output: [1,2,3,4]
     *
     *  Input: adjacentPairs = [[4,-2],[1,4],[-3,1]]
     *  Output: [-2,4,1,-3]
     *
     *  Input: adjacentPairs = [[100000,-100000]]
     *  Output: [100000,-100000]
     */

    int** pAdjacentPairs = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: adjacentPairs = [");
        for (j = 0; j < testCase[i].adjacentPairsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].adjacentPairsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].adjacentPairs[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pAdjacentPairs = (int**)malloc(testCase[i].adjacentPairsSize * sizeof(int*));
        if (pAdjacentPairs == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].adjacentPairsSize; ++j) {
            pAdjacentPairs[j] = (int*)malloc(testCase[i].adjacentPairsColSize[j] * sizeof(int));
            if (pAdjacentPairs[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pAdjacentPairs[k]);
                }
                free(pAdjacentPairs);
                return EXIT_FAILURE;
            }
            memset(pAdjacentPairs[j], 0, (testCase[i].adjacentPairsColSize[j] * sizeof(int)));
            memcpy(pAdjacentPairs[j], testCase[i].adjacentPairs[j],
                   (testCase[i].adjacentPairsColSize[j] * sizeof(int)));
        }
        pAnswer = restoreArray(pAdjacentPairs, testCase[i].adjacentPairsSize, testCase[i].adjacentPairsColSize,
                               &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].adjacentPairsSize; ++j) {
            free(pAdjacentPairs[j]);
        }
        free(pAdjacentPairs);
        pAdjacentPairs = NULL;
    }

    return EXIT_SUCCESS;
}
