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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *queryResults(int limit, int **queries, int queriesSize, int *queriesColSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int *)calloc(queriesSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return NULL;
    }

    struct hashTable *pColorHashTable = NULL;
    struct hashTable *pBallHashTable = NULL;
    struct hashTable *pTemp;
    int ball, color, prevColor;
    for (int i = 0; i < queriesSize; i++) {
        ball = queries[i][0];
        color = queries[i][1];

        pTemp = NULL;
        HASH_FIND_INT(pBallHashTable, &ball, pTemp);
        if (pTemp != NULL) {
            // Decrement count of the previous color on the ball
            prevColor = pTemp->value;
            pTemp->value = color;

            pTemp = NULL;
            HASH_FIND_INT(pColorHashTable, &prevColor, pTemp);
            if (pTemp != NULL) {
                pTemp->value--;
                // If there are no balls with previous color left, remove color from color map
                if (pTemp->value == 0) {
                    HASH_DEL(pColorHashTable, pTemp);
                    free(pTemp);
                }
            }
        } else {
            // Set color of ball to the new color
            pTemp = NULL;
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pColorHashTable);
                freeAll(pBallHashTable);
                free(pRetVal);
                pRetVal = NULL;
                return pRetVal;
            }
            pTemp->key = ball;
            pTemp->value = color;
            HASH_ADD_INT(pBallHashTable, key, pTemp);
        }

        // Increment the count of the new color
        pTemp = NULL;
        HASH_FIND_INT(pColorHashTable, &color, pTemp);
        if (pTemp == NULL) {
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                freeAll(pColorHashTable);
                freeAll(pBallHashTable);
                free(pRetVal);
                pRetVal = NULL;
                return pRetVal;
            }
            pTemp->key = color;
            pTemp->value = 1;
            HASH_ADD_INT(pColorHashTable, key, pTemp);
        } else {
            pTemp->value += 1;
        }

        pRetVal[i] = HASH_COUNT(pColorHashTable);
        (*returnSize)++;
    }

    //
    freeAll(pColorHashTable);
    freeAll(pBallHashTable);

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int limit;
        int queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{4, {{1, 4}, {2, 5}, {1, 3}, {3, 4}}, 4, {2, 2, 2, 2}, 0},
                    {4, {{0, 1}, {1, 2}, {2, 2}, {3, 4}, {4, 5}}, 5, {2, 2, 2, 2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4]]
     *  Output: [1,2,2,3]
     *
     *  Input: limit = 4, queries = [[0,1],[1,2],[2,2],[3,4],[4,5]]
     *  Output: [1,2,2,3,4]
     */

    int **pQueries = NULL;
    int *pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: limit = %d, queries =  [", testCase[i].limit);
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].queriesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].queries[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pQueries = (int **)malloc(testCase[i].queriesSize * sizeof(int *));
        if (pQueries == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (int *)malloc(testCase[i].queriesColSize[j] * sizeof(int));
            if (pQueries[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pQueries[k]) {
                        free(pQueries[k]);
                        pQueries[k] = NULL;
                    }
                }
                free(pQueries);
                pQueries = NULL;
                return EXIT_FAILURE;
            }
            memset(pQueries[j], 0, testCase[i].queriesColSize[j] * sizeof(int));
            memcpy(pQueries[j], testCase[i].queries[j], testCase[i].queriesColSize[j] * sizeof(int));
        }
        pAnswer = queryResults(testCase[i].limit, pQueries, testCase[i].queriesSize, testCase[i].queriesColSize,
                               &testCase[i].returnSize);
        printf("Output:[");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            if (pQueries[j]) {
                free(pQueries[j]);
                pQueries[j] = NULL;
            }
        }
        free(pQueries);
        pQueries = NULL;
    }

    return EXIT_SUCCESS;
}
