#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMinHeightTrees(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    if (n == 1) {
        pRetVal = (int*)malloc(1 * sizeof(int));
        if (pRetVal == NULL) {
            perror("malloc");
            return pRetVal;
        }
        memset(pRetVal, 0, (1 * sizeof(int)));
        pRetVal[(*returnSize)] = 0;
        (*returnSize)++;
        return pRetVal;
    }

    int i;
    struct ListNode* pFree = NULL;

    struct ListNode* adjacency[n];
    for (i = 0; i < n; i++) {
        adjacency[i] = NULL;
    }
    int degree[n];
    memset(degree, 0, (n * sizeof(int)));
    struct ListNode* pNode = NULL;
    int src, dst;
    for (i = 0; i < edgesSize; i++) {
        src = edges[i][0];
        dst = edges[i][1];

        pNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pNode == NULL) {
            perror("malloc");
            for (i = 0; i < n; i++) {
                while (adjacency[i] != NULL) {
                    pFree = adjacency[i];
                    adjacency[i] = pFree->next;
                    free(pFree);
                    pFree = NULL;
                }
            }
            return pRetVal;
        }
        pNode->val = src;
        pNode->next = adjacency[dst];
        adjacency[dst] = pNode;

        pNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pNode == NULL) {
            perror("malloc");
            for (i = 0; i < n; i++) {
                while (adjacency[i] != NULL) {
                    pFree = adjacency[i];
                    adjacency[i] = pFree->next;
                    free(pFree);
                    pFree = NULL;
                }
            }
            return pRetVal;
        }
        pNode->val = dst;
        pNode->next = adjacency[src];
        adjacency[src] = pNode;

        degree[src]++;
        degree[dst]++;
    }

    int queue[n];
    memset(queue, 0, sizeof(queue));
    int queueHead = 0;
    int queueTail = 0;
    for (i = 0; i < n; i++) {
        if (degree[i] == 1) {
            queue[queueTail] = i;
            queueTail++;
        }
    }

    int vertex;
    struct ListNode* pCurrent = NULL;
    int node;
    int queueSize;
    int remainNodes = n;
    while (remainNodes > 2) {
        queueSize = queueTail - queueHead;
        remainNodes -= queueSize;
        for (i = 0; i < queueSize; i++) {
            node = queue[queueHead];
            queueHead++;
            pCurrent = adjacency[node];
            while (pCurrent != NULL) {
                vertex = pCurrent->val;
                degree[vertex]--;
                if (degree[vertex] == 1) {
                    queue[queueTail] = vertex;
                    queueTail++;
                }
                pCurrent = pCurrent->next;
            }
        }
    }

    pRetVal = (int*)malloc(remainNodes * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        for (i = 0; i < n; i++) {
            while (adjacency[i] != NULL) {
                pFree = adjacency[i];
                adjacency[i] = pFree->next;
                free(pFree);
                pFree = NULL;
            }
        }
        return pRetVal;
    }
    while (queueHead != queueTail) {
        pRetVal[(*returnSize)++] = queue[queueHead++];
    }

    for (i = 0; i < n; i++) {
        while (adjacency[i] != NULL) {
            pFree = adjacency[i];
            adjacency[i] = pFree->next;
            free(pFree);
            pFree = NULL;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 10000)
    struct testCaseType {
        int n;
        int edges[MAX_SIZE][2];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{4, {{1, 0}, {1, 2}, {1, 3}}, 3, {2, 2, 2}, 0},
                    {6, {{3, 0}, {3, 1}, {3, 2}, {3, 4}, {5, 4}}, 5, {2, 2, 2, 2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4, edges = [[1,0],[1,2],[1,3]]
     *  Output: [1]
     *
     *  Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
     *  Output: [3,4]
     */

    int** pEdges = NULL;
    int* pAnswer = NULL;
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

        pEdges = (int**)malloc(testCase[i].edgesSize * sizeof(int*));
        if (pEdges == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            pEdges[j] = (int*)malloc(testCase[i].edgesColSize[j] * sizeof(int));
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
        pAnswer = findMinHeightTrees(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize,
                                     &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

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
