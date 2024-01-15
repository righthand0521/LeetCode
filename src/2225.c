#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
struct hashStruct {
    int id;
    int win;
    int lose;
    UT_hash_handle hh;
};
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findWinners(int** matches, int matchesSize, int* matchesColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 2;
    int i, j;

    // malloc return value
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = (int*)malloc(matchesSize * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(pRetVal[i], 0, (matchesSize * sizeof(int)));
    }

    // record win and lose
    struct hashStruct* pMap = NULL;
    struct hashStruct* pTmp;
    for (i = 0; i < matchesSize; ++i) {
        // win
        pTmp = NULL;
        HASH_FIND_INT(pMap, &matches[i][0], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pMap);
                return pRetVal;
            }
            pTmp->id = matches[i][0];
            pTmp->win = 1;
            pTmp->lose = 0;
            HASH_ADD_INT(pMap, id, pTmp);
        } else {
            pTmp->win++;
        }

        // lose
        pTmp = NULL;
        HASH_FIND_INT(pMap, &matches[i][1], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashStruct*)malloc(sizeof(struct hashStruct));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pMap);
                return pRetVal;
            }
            pTmp->id = matches[i][1];
            pTmp->win = 0;
            pTmp->lose = 1;
            HASH_ADD_INT(pMap, id, pTmp);
        } else {
            pTmp->lose++;
        }
    }

    // answer[0] is a list of all players that have not lost any matches.
    // answer[1] is a list of all players that have lost exactly one match.
    (*returnColumnSizes)[0] = 0;
    (*returnColumnSizes)[1] = 0;
    pTmp = NULL;
    for (pTmp = pMap; pTmp != NULL; pTmp = pTmp->hh.next) {
        // printf("[%d](%d, %d)\n", pTmp->id, pTmp->win, pTmp->lose);

        if (pTmp->lose == 0) {
            pRetVal[0][(*returnColumnSizes)[0]] = pTmp->id;
            (*returnColumnSizes)[0]++;
        } else if (pTmp->lose == 1) {
            pRetVal[1][(*returnColumnSizes)[1]] = pTmp->id;
            (*returnColumnSizes)[1]++;
        }
    }
    freeAll(pMap);

    // The values in the two lists should be returned in increasing order.
    qsort(pRetVal[0], (*returnColumnSizes)[0], sizeof(int), compareInteger);
    qsort(pRetVal[1], (*returnColumnSizes)[1], sizeof(int), compareInteger);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int matches[MAX_SIZE][2];
        int matchesSize;
        int matchesColSize[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 3}, {2, 3}, {3, 6}, {5, 6}, {5, 7}, {4, 5}, {4, 8}, {4, 9}, {10, 4}, {10, 9}},
                     10,
                     {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                     0,
                     NULL},
                    {{{2, 3}, {1, 3}, {5, 4}, {6, 4}}, 4, {2, 2, 2, 2}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matches = [[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]]
     *  Output: [[1,2,10],[4,5,7,8]]
     *
     *  Input: matches = [[2,3],[1,3],[5,4],[6,4]]
     *  Output: [[1,2,5,6],[]]
     */

    int** pMatches = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: matches =  [");
        for (j = 0; j < testCase[i].matchesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].matchesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].matches[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pMatches = (int**)malloc(testCase[i].matchesSize * sizeof(int*));
        if (pMatches == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].matchesSize; ++j) {
            pMatches[j] = (int*)malloc(testCase[i].matchesColSize[j] * sizeof(int));
            if (pMatches[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pMatches[k]);
                    pMatches[k] = NULL;
                }
                free(pMatches);
                pMatches = NULL;
                return EXIT_FAILURE;
            }
            memset(pMatches[j], 0, testCase[i].matchesColSize[j] * sizeof(int));
            memcpy(pMatches[j], testCase[i].matches[j], testCase[i].matchesColSize[j] * sizeof(int));
        }
        pAnswer = findWinners(pMatches, testCase[i].matchesSize, testCase[i].matchesColSize, &testCase[i].returnSize,
                              &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;

        for (j = 0; j < testCase[i].matchesSize; ++j) {
            if (pMatches[j]) {
                free(pMatches[j]);
                pMatches[j] = NULL;
            }
        }
        free(pMatches);
        pMatches = NULL;
    }

    return EXIT_SUCCESS;
}
