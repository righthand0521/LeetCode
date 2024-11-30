#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

// https://leetcode.cn/problems/valid-arrangement-of-pairs/solutions/1175305/qing-cha-shou-ben-ti-de-di-yi-ge-cyu-yan-sru0/
struct hashTable {
    int key;
    int id;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->id);
        HASH_DEL(pFree, current);
        free(current);
    }
}
void dfs(int x, int **edges, int **edgesColSize, int **answer, int *answerSize) {
    int y;
    while ((*edgesColSize)[x] > 0) {
        y = edges[x][(*edgesColSize)[x] - 1];
        (*edgesColSize)[x]--;

        dfs(y, edges, edgesColSize, answer, answerSize);

        answer[(*answerSize)][0] = x;
        answer[(*answerSize)][1] = y;
        (*answerSize)++;
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **validArrangement(int **pairs, int pairsSize, int *pairsColSize, int *returnSize, int **returnColumnSizes) {
    int **pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    int i, j;

    //
    (*returnColumnSizes) = (int *)calloc(pairsSize, sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("calloc");
        return pRetVal;
    }
    pRetVal = (int **)malloc(sizeof(int *) * pairsSize);
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit_returnColumnSizes;
    }
    for (i = 0; i < pairsSize; ++i) {
        (*returnColumnSizes)[i] = 2;
        pRetVal[i] = (int *)calloc((*returnColumnSizes)[i], sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("calloc");
            goto exit_returnSize;
        }
    }

    //
    int *basicSize = (int *)calloc((pairsSize + 1), sizeof(int));
    if (basicSize == NULL) {
        perror("calloc");
        goto exit_returnSize;
    }
    int *edgesColSize = (int *)calloc((pairsSize + 1), sizeof(int));
    if (edgesColSize == NULL) {
        perror("calloc");
        goto exit_basicSize;
    }
    int **edges = (int **)malloc((pairsSize + 1) * sizeof(int *));
    if (edges == NULL) {
        perror("calloc");
        goto exit_edgesColSize;
    }
    for (i = 0; i < pairsSize + 1; i++) {
        edgesColSize[i] = 0;
        basicSize[i] = 8;
        edges[i] = (int *)calloc(basicSize[i], sizeof(int));
        if (edges[i] == NULL) {
            perror("calloc");
            goto exit_edges;
        }
    }
    //
    int *inDegree = (int *)calloc((pairsSize + 1), sizeof(int));
    if (inDegree == NULL) {
        perror("calloc");
        goto exit_edges;
    }
    int *outDegree = (int *)calloc((pairsSize + 1), sizeof(int));
    if (outDegree == NULL) {
        perror("calloc");
        goto exit_inDegree;
    }
    int *sign = (int *)calloc((pairsSize + 1), sizeof(int));
    if (sign == NULL) {
        perror("calloc");
        goto exit_outDegree;
    }
    //

    struct hashTable *pUser = NULL;
    struct hashTable *pTmp;
    int x, y, indexX, indexY;
    int count = 0;
    for (j = 0; j < pairsSize; ++j) {
        x = pairs[j][0];
        y = pairs[j][1];

        pTmp = NULL;
        HASH_FIND_INT(pUser, &x, pTmp);
        if (pTmp == NULL) {
            indexX = count;
            sign[indexX] = x;
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                goto exit_hashTable;
            }
            pTmp->key = x;
            pTmp->id = count++;
            HASH_ADD_INT(pUser, key, pTmp);
        } else {
            indexX = pTmp->id;
        }

        pTmp = NULL;
        HASH_FIND_INT(pUser, &y, pTmp);
        if (pTmp == NULL) {
            indexY = count;
            sign[indexY] = y;
            pTmp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                goto exit_hashTable;
            }
            pTmp->key = y;
            pTmp->id = count++;
            HASH_ADD_INT(pUser, key, pTmp);
        } else {
            indexY = pTmp->id;
        }

        outDegree[indexX]++;
        inDegree[indexY]++;
        edgesColSize[indexX]++;
        if (edgesColSize[indexX] == basicSize[indexX]) {
            basicSize[indexX] *= 2;
            edges[indexX] = (int *)realloc(edges[indexX], basicSize[indexX] * sizeof(int));
            if (edges[indexX] == NULL) {
                perror("realloc");
                goto exit_hashTable;
            }
        }
        edges[indexX][edgesColSize[indexX] - 1] = indexY;
    }

    int start = 0;
    for (j = 0; j < count; ++j) {
        if (inDegree[j] == outDegree[j] - 1) {
            start = j;
        }
    }

    dfs(start, edges, &edgesColSize, pRetVal, returnSize);

    int temp0, temp1;
    for (j = 0; j < (*returnSize) / 2; ++j) {
        temp0 = pRetVal[j][0];
        temp1 = pRetVal[j][1];

        pRetVal[j][0] = sign[pRetVal[(*returnSize) - j - 1][0]];
        pRetVal[j][1] = sign[pRetVal[(*returnSize) - j - 1][1]];

        pRetVal[(*returnSize) - j - 1][0] = sign[temp0];
        pRetVal[(*returnSize) - j - 1][1] = sign[temp1];
    }

    if ((*returnSize) % 2 == 1) {
        j = (*returnSize) / 2;
        pRetVal[j][0] = sign[pRetVal[j][0]];
        pRetVal[j][1] = sign[pRetVal[j][1]];
    }

    (*returnSize) = pairsSize;

exit_hashTable:
    freeAll(pUser);
    pUser = NULL;
    // exit_sign:
    free(sign);
    sign = NULL;
exit_outDegree:
    free(outDegree);
    outDegree = NULL;
exit_inDegree:
    free(inDegree);
    inDegree = NULL;
exit_edges:
    for (j = 0; j < i; ++j) {
        free(edges[j]);
        edges[j] = NULL;
    }
    i = pairsSize;
    free(edges);
    edges = NULL;
exit_edgesColSize:
    free(edgesColSize);
    edgesColSize = NULL;
exit_basicSize:
    free(basicSize);
    basicSize = NULL;
exit_returnSize:
    if ((*returnSize) == 0) {
        for (j = 0; j < i; ++j) {
            free(pRetVal[j]);
            pRetVal[j] = NULL;
        }
        free(pRetVal);
        pRetVal = NULL;
    }
exit_returnColumnSizes:
    if ((*returnSize) == 0) {
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_ROW (int)(1e5)
#define MAX_COLUMN (2)
    struct testCaseType {
        int pairs[MAX_ROW][MAX_COLUMN];
        int pairsSize;
        int pairsColSize[MAX_ROW];
        int returnSize;
        int *returnColumnSizes;
    } testCase[] = {{{{5, 1}, {4, 5}, {11, 9}, {9, 4}}, 4, {2, 2, 2, 2}, 0, NULL},
                    {{{1, 3}, {3, 2}, {2, 1}}, 3, {2, 2, 2}, 0, NULL},
                    {{{1, 2}, {1, 3}, {2, 1}}, 3, {2, 2, 2}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
     *  Output: [[11,9],[9,4],[4,5],[5,1]]
     *
     *  Input: pairs = [[1,3],[3,2],[2,1]]
     *  Output: [[1,3],[3,2],[2,1]]
     *
     *  Input: pairs = [[1,2],[1,3],[2,1]]
     *  Output: [[1,2],[2,1],[1,3]]
     */

    int **pPairs = NULL;
    int **pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: pairs = [");
        for (j = 0; j < testCase[i].pairsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].pairsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].pairs[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pPairs = (int **)malloc(testCase[i].pairsSize * sizeof(int *));
        if (pPairs == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].pairsSize; ++j) {
            pPairs[j] = (int *)malloc(testCase[i].pairsColSize[j] * sizeof(int));
            if (pPairs[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pPairs[k]);
                }
                free(pPairs);
                return EXIT_FAILURE;
            }
            memset(pPairs[j], 0, (testCase[i].pairsColSize[j] * sizeof(int)));
            memcpy(pPairs[j], testCase[i].pairs[j], (testCase[i].pairsColSize[j] * sizeof(int)));
        }

        pAnswer = validArrangement(pPairs, testCase[i].pairsSize, testCase[i].pairsColSize, &testCase[i].returnSize,
                                   &(testCase[i].returnColumnSizes));
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), pAnswer[j][k]);
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
        for (j = 0; j < testCase[i].pairsSize; ++j) {
            free(pPairs[j]);
            pPairs[j] = NULL;
        }
        free(pPairs);
        pPairs = NULL;
    }

    return EXIT_SUCCESS;
}
