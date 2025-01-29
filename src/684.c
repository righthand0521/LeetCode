#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cycleStart = -1;
void dfs(int src, bool* visited, int** adjList, int adjListSize, int* parent) {
    visited[src] = true;

    int adj;
    for (int i = 0; i < adjListSize; ++i) {
        adj = adjList[src][i];
        if (adj == -1) {
            continue;
        }

        if (visited[adj] == false) {
            parent[adj] = src;
            dfs(adj, visited, adjList, adjListSize, parent);
        } else if ((adj != parent[src]) && (cycleStart == -1)) {
            // If the node is visited and the parent is different then the node is part of the cycle.
            cycleStart = adj;
            parent[adj] = src;
        }
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    int* pRetVal = NULL;

    cycleStart = -1;

    (*returnSize) = 0;

    int** pAdjList = NULL;
    pAdjList = (int**)malloc(edgesSize * sizeof(int*));
    if (pAdjList == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (int i = 0; i < edgesSize; ++i) {
        pAdjList[i] = (int*)malloc(edgesSize * sizeof(int));
        if (pAdjList[i] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; ++j) {
                free(pAdjList[j]);
                pAdjList[j] = NULL;
            }
            free(pAdjList);
            pAdjList = NULL;
            return pRetVal;
        }
        for (int j = 0; j < edgesSize; ++j) {
            pAdjList[i][j] = -1;
        }
    }
    for (int i = 0; i < edgesSize; ++i) {
        int src = edges[i][0] - 1;
        int dst = edges[i][1] - 1;
        pAdjList[src][dst] = dst;
        pAdjList[dst][src] = src;
    }

    bool* pVisited = NULL;
    pVisited = (bool*)malloc(edgesSize * sizeof(bool));
    if (pVisited == NULL) {
        perror("malloc");
        goto exit_pAdjList;
    }
    memset(pVisited, false, (edgesSize * sizeof(bool)));
    int* pParent = NULL;
    pParent = (int*)malloc(edgesSize * sizeof(int));
    if (pParent == NULL) {
        perror("malloc");
        goto exit_pVisited;
    }
    for (int i = 0; i < edgesSize; ++i) {
        pParent[i] = -1;
    }
    dfs(0, pVisited, pAdjList, edgesSize, pParent);

    // Start from the cycleStart node and backtrack to get all the nodes in the cycle. Mark them all in the map.
    int cycleNodes[1000 + 4];  // given a graph that started as a tree with n nodes labeled from 1 to n, 3 <= n <= 1000.
    memset(cycleNodes, 0, sizeof(cycleNodes));
    int node = cycleStart;
    do {
        cycleNodes[node] = 1;
        node = pParent[node];
    } while (node != cycleStart);

    // If both nodes of the edge were marked as cycle nodes then this edge can be removed.
    for (int i = edgesSize - 1; i >= 0; i--) {
        if ((cycleNodes[edges[i][0] - 1]) && (cycleNodes[edges[i][1] - 1])) {
            pRetVal = (int*)calloc(edgesColSize[i], sizeof(int));
            if (pRetVal == NULL) {
                perror("calloc");
                break;
            }
            memcpy(pRetVal, edges[i], (edgesColSize[i] * sizeof(int)));
            (*returnSize) = edgesColSize[i];
            break;
        }
    }

    //
    free(pParent);
    pParent = NULL;
exit_pVisited:
    free(pVisited);
    pVisited = NULL;
exit_pAdjList:
    for (int i = 0; i < edgesSize; ++i) {
        free(pAdjList[i]);
        pAdjList[i] = NULL;
    }
    free(pAdjList);
    pAdjList = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int edges[MAX_SIZE][2];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{{{1, 2}, {1, 3}, {2, 3}}, 3, {2, 2, 2}, 0},
                    {{{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}}, 5, {2, 2, 2, 2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: edges = [[1,2],[1,3],[2,3]]
     *  Output: [2,3]
     *
     *  Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
     *  Output: [1,4]
     */

    int** pEdges = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: edges =  [");
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
        pAnswer =
            findRedundantConnection(pEdges, testCase[i].edgesSize, testCase[i].edgesColSize, &testCase[i].returnSize);
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
