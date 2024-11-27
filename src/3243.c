#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;
typedef struct List {
    Node *node;
} List;
int push(List *pObj, int val) {
    int retVal = EXIT_SUCCESS;

    Node *pNew = (Node *)malloc(sizeof(Node));
    if (pNew == NULL) {
        perror("malloc");
        retVal = EXIT_FAILURE;
        return retVal;
    }
    pNew->next = pObj->node;
    pNew->val = val;

    pObj->node = pNew;

    return retVal;
}
void freeList(List *pObj) {
    Node *pFree;
    Node *pCurrent;
    for (pCurrent = pObj->node; pCurrent != NULL;) {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        free(pFree);
        pFree = NULL;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *shortestDistanceAfterQueries(int n, int **queries, int queriesSize, int *queriesColSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    int i, j;

    List *adjacency = (List *)malloc(n * sizeof(List));
    if (adjacency == NULL) {
        perror("malloc");
        goto exit;
    }
    memset(adjacency, 0, n * sizeof(List));

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        perror("malloc");
        goto exit_adjacency;
    }
    memset(dp, 0, n * sizeof(int));

    for (i = 1; i < n; ++i) {
        if (push(&adjacency[i], i - 1) == EXIT_FAILURE) {
            goto exit_dp;
        }
        dp[i] = i;
    }

    pRetVal = (int *)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit_dp;
    }

    Node *pCurrent;
    for (i = 0; i < queriesSize; ++i) {
        if (push(&adjacency[queries[i][1]], queries[i][0]) == EXIT_FAILURE) {
            i = n;
            goto exit_dp;
        }

        for (j = queries[i][1]; j < n; ++j) {
            for (pCurrent = adjacency[j].node; pCurrent != NULL; pCurrent = pCurrent->next) {
                dp[j] = fmin(dp[j], dp[pCurrent->val] + 1);
            }
        }
        pRetVal[i] = dp[n - 1];
    }
    (*returnSize) = queriesSize;
    i = n;

exit_dp:
    free(dp);
    dp = NULL;

    for (j = 0; j < i; ++j) {
        freeList(&adjacency[j]);
    }

exit_adjacency:
    free(adjacency);
    adjacency = NULL;

exit:
    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int n;
        int queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{5, {{2, 4}, {0, 2}, {0, 4}}, 3, {2, 2, 2}, 0}, {4, {{0, 3}, {0, 2}}, 2, {2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, queries = [[2,4],[0,2],[0,4]]
     *  Output: [3,2,1]
     *
     *  Input: n = 4, queries = [[0,3],[0,2]]
     *  Output: [1,1]
     */

    int **pQueries = NULL;
    int *pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, queries =  [", testCase[i].n);
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
        pAnswer = shortestDistanceAfterQueries(testCase[i].n, pQueries, testCase[i].queriesSize,
                                               testCase[i].queriesColSize, &testCase[i].returnSize);
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
