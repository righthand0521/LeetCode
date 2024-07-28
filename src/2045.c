#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int val;
    struct Node *next;
};
int pushNode(struct Node **pObj, int value) {
    int retVal = EXIT_SUCCESS;

    struct Node *pNode = (struct Node *)malloc(sizeof(struct Node));
    if (pNode == NULL) {
        perror("malloc");
        retVal = EXIT_FAILURE;
        return retVal;
    }
    pNode->val = value;
    pNode->next = (*pObj);

    (*pObj) = pNode;

    return retVal;
}
void freeNode(struct Node *pObj) {
    struct Node *pFree;
    while (pObj != NULL) {
        pFree = pObj;
        pObj = pObj->next;
        free(pFree);
        pFree = NULL;
    }
}
int secondMinimum(int n, int **edges, int edgesSize, int *edgesColSize, int time, int change) {
    int retVal = 0;

    int i;

    //
    int pAdjacencySize = n + 1;
    struct Node **pAdjacency = (struct Node **)malloc(pAdjacencySize * sizeof(struct Node *));
    if (pAdjacency == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pAdjacency, 0, (pAdjacencySize * sizeof(struct Node *)));
    int ret;
    for (i = 0; i < edgesSize; i++) {
        ret = pushNode(&pAdjacency[edges[i][0]], edges[i][1]);
        if (ret == EXIT_FAILURE) {
            goto exit_pAdjacency;
        }

        ret = pushNode(&pAdjacency[edges[i][1]], edges[i][0]);
        if (ret == EXIT_FAILURE) {
            goto exit_pAdjacency;
        }
    }

    //
    int pPathSize = 2 * n + 1;
    int *pPath = (int *)malloc(pPathSize * sizeof(int));
    if (pPath == NULL) {
        perror("malloc");
        goto exit_pAdjacency;
    }
    memset(pPath, 0, (pPathSize * sizeof(int)));
    for (i = 1; i <= n; i++) {
        pPath[i] = INT_MAX;
        pPath[i + n] = INT_MAX;
    }
    pPath[1] = 0;

    //
    struct Pair {
        int node;
        int len;
    };
    int pBfsQueueSize = 2 * n + 1;
    struct Pair *pBfsQueue = (struct Pair *)malloc(pBfsQueueSize * sizeof(struct Pair));
    if (pPath == NULL) {
        perror("malloc");
        goto exit_pPath;
    }
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    pBfsQueue[bfsQueueTail].node = 1;
    pBfsQueue[bfsQueueTail++].len = 0;

    //
    struct Node *pCurrent;
    int node, len;
    while (pPath[n + n] == INT_MAX) {
        node = pBfsQueue[bfsQueueHead].node;
        len = pBfsQueue[bfsQueueHead++].len;

        pCurrent = pAdjacency[node];
        while (pCurrent != NULL) {
            if (len + 1 < pPath[pCurrent->val]) {
                pPath[pCurrent->val] = len + 1;
                pBfsQueue[bfsQueueTail].node = pCurrent->val;
                pBfsQueue[bfsQueueTail++].len = len + 1;
            } else if ((len + 1 > pPath[pCurrent->val]) && (len + 1 < pPath[pCurrent->val + n])) {
                pPath[pCurrent->val + n] = len + 1;
                pBfsQueue[bfsQueueTail].node = pCurrent->val;
                pBfsQueue[bfsQueueTail++].len = len + 1;
            }

            pCurrent = pCurrent->next;
        }
    }

    //
    for (i = 0; i < pPath[n + n]; i++) {
        if (retVal % (2 * change) >= change) {
            retVal = retVal + 2 * change - retVal % (2 * change);
        }

        retVal += time;
    }

    //
    free(pBfsQueue);
    pBfsQueue = NULL;

exit_pPath:
    free(pPath);
    pPath = NULL;

exit_pAdjacency:
    for (i = 1; i <= n; i++) {
        freeNode(pAdjacency[i]);
        pAdjacency[i] = NULL;
    }
    free(pAdjacency);
    pAdjacency = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_ROW_SIZE (2 * 10000)
#define MAX_COL_SIZE (2)
    struct testCaseType {
        int n;
        int edges[MAX_ROW_SIZE][MAX_COL_SIZE];
        int edgesSize;
        int edgesColSize[MAX_ROW_SIZE];
        int time;
        int change;
    } testCase[] = {{5, {{1, 2}, {1, 3}, {1, 4}, {3, 4}, {4, 5}}, 5, {2, 2, 2, 2, 2}, 3, 5},
                    {2, {{1, 2}}, 1, {2}, 3, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, edges = [[1,2],[1,3],[1,4],[3,4],[4,5]], time = 3, change = 5
     *  Output: 13
     *
     *  Input: n = 2, edges = [[1,2]], time = 3, change = 2
     *  Output: 11
     */

    int **pEdges = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, edges = [", testCase[i].n);
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges[j][k]);
            }
            printf("]");
        }
        printf("], time = %d, change = %d\n", testCase[i].time, testCase[i].change);

        pEdges = (int **)malloc(testCase[i].edgesSize * sizeof(int *));
        if (pEdges == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            pEdges[j] = (int *)malloc(testCase[i].edgesColSize[j] * sizeof(int));
            if (pEdges[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pEdges[k]);
                    pEdges[k] = NULL;
                }
                free(pEdges);
                pEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, (testCase[i].edgesColSize[j] * sizeof(int)));
            memcpy(pEdges[j], testCase[i].edges[j], (testCase[i].edgesColSize[j] * sizeof(int)));
        }
        answer = secondMinimum(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize, testCase[i].time,
                               testCase[i].change);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].edgesSize; ++j) {
            free(pEdges[j]);
            pEdges[j] = NULL;
        }
        free(pEdges);
        pEdges = NULL;
    }

    return EXIT_SUCCESS;
}
