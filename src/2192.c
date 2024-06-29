#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    UT_hash_handle hh;
};
struct hashTable *hashFindItem(struct hashTable **obj, int key) {
    struct hashTable *pRetVal = NULL;

    HASH_FIND_INT(*obj, &key, pRetVal);

    return pRetVal;
}
bool hashAddItem(struct hashTable **obj, int key) {
    bool retVal = false;

    if (hashFindItem(obj, key)) {
        return retVal;
    }
    struct hashTable *pEntry = (struct hashTable *)malloc(sizeof(struct hashTable));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = key;
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
void freeAll(struct hashTable **pFree) {
    struct hashTable *current = NULL;
    struct hashTable *tmp = NULL;
    HASH_ITER(hh, (*pFree), current, tmp) {
        // printf("%d\n", (*pFree)->key);
        HASH_DEL((*pFree), current);
        free(current);
    }
}
struct ListNode *creatListNode(int val) {
    struct ListNode *pRetVal = NULL;

    pRetVal = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = val;
    pRetVal->next = NULL;

    return pRetVal;
}
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **getAncestors(int n, int **edges, int edgesSize, int *edgesColSize, int *returnSize, int **returnColumnSizes) {
    int **pRetVal = NULL;

    (*returnSize) = 0;

    //
    pRetVal = (int **)malloc(n * sizeof(int *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int *)malloc(n * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (n * sizeof(int)));

    //
    int i;

    //
    struct hashTable *ancestorsSetList[n];
    struct ListNode *adjacencyList[n];
    int indegree[n];
    for (i = 0; i < n; i++) {
        ancestorsSetList[i] = NULL;
        adjacencyList[i] = NULL;
        indegree[i] = 0;
    }
    struct ListNode *pNode;
    int from, to;
    for (i = 0; i < edgesSize; i++) {
        from = edges[i][0];
        to = edges[i][1];

        pNode = creatListNode(to);
        if (pNode == NULL) {
            continue;
        }
        pNode->next = adjacencyList[from];
        adjacencyList[from] = pNode;
        indegree[to] += 1;
    }

    //
    int nodesWithZeroIndegree[n];
    int nodesWithZeroIndegreeHead = 0;
    int nodesWithZeroIndegreeTail = 0;
    for (i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            nodesWithZeroIndegree[nodesWithZeroIndegreeTail++] = i;
        }
    }
    struct hashTable *pEntry;
    int currentNode, key, value;
    while (nodesWithZeroIndegreeHead != nodesWithZeroIndegreeTail) {
        currentNode = nodesWithZeroIndegree[nodesWithZeroIndegreeHead++];
        for (pNode = adjacencyList[currentNode]; pNode; pNode = pNode->next) {
            value = pNode->val;
            hashAddItem(&ancestorsSetList[value], currentNode);

            for (pEntry = ancestorsSetList[currentNode]; pEntry != NULL; pEntry = pEntry->hh.next) {
                key = pEntry->key;
                hashAddItem(&ancestorsSetList[value], key);
            }

            indegree[value] -= 1;
            if (indegree[value] == 0) {
                nodesWithZeroIndegree[nodesWithZeroIndegreeTail++] = value;
            }
        }
    }

    //
    int idx;
    int ancestorsSetListCount;
    for (i = 0; i < n; ++i) {
        ancestorsSetListCount = HASH_COUNT(ancestorsSetList[i]);

        (*returnColumnSizes)[i] = ancestorsSetListCount;
        pRetVal[i] = (int *)malloc(ancestorsSetListCount * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            continue;
        }
        memset(pRetVal[i], 0, (ancestorsSetListCount * sizeof(int)));
        (*returnSize) += 1;
        idx = 0;
        for (pEntry = ancestorsSetList[i]; pEntry != NULL; pEntry = pEntry->hh.next) {
            pRetVal[i][idx++] = pEntry->key;
        }
        qsort(pRetVal[i], ancestorsSetListCount, sizeof(int), compareInteger);

        freeAll(&ancestorsSetList[i]);
        ancestorsSetList[i] = NULL;
        while (adjacencyList[i] != NULL) {
            pNode = adjacencyList[i];
            adjacencyList[i] = adjacencyList[i]->next;
            free(pNode);
            pNode = NULL;
        }
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int n;
        int edges[MAX_SIZE][2];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        int returnSize;
        int *returnColumnSizes;
    } testCase[] = {{8,
                     {{0, 3}, {0, 4}, {1, 3}, {2, 4}, {2, 7}, {3, 5}, {3, 6}, {3, 7}, {4, 6}},
                     9,
                     {2, 2, 2, 2, 2, 2, 2, 2, 2},
                     0,
                     NULL},
                    {5,
                     {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}},
                     10,
                     {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                     0,
                     NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 8, edgeList = [[0,3],[0,4],[1,3],[2,4],[2,7],[3,5],[3,6],[3,7],[4,6]]
     *  Output: [[],[],[],[0,1],[0,2],[0,1,3],[0,1,2,3,4],[0,1,2,3]]
     *
     *  Input: n = 5, edgeList = [[0,1],[0,2],[0,3],[0,4],[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
     *  Output: [[],[0],[0,1],[0,1,2],[0,1,2,3]]
     */

    int **pEdges = NULL;
    int **pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, edges =  [", testCase[i].n);
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges[j][k]);
            }
            printf("]");
        }
        printf("]\n");

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
                    if (pEdges[k]) {
                        free(pEdges[k]);
                        pEdges[k] = NULL;
                    }
                }
                free(pEdges);
                pEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, testCase[i].edgesColSize[j] * sizeof(int));
            memcpy(pEdges[j], testCase[i].edges[j], testCase[i].edgesColSize[j] * sizeof(int));
        }
        pAnswer = getAncestors(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize,
                               &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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

        for (j = 0; j < testCase[i].edgesSize; ++j) {
            if (pEdges[j]) {
                free(pEdges[j]);
                pEdges[j] = NULL;
            }
        }
        free(pEdges);
        pEdges = NULL;
    }

    return EXIT_SUCCESS;
}
