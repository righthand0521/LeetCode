#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* eventualSafeNodes(int** graph, int graphSize, int* graphColSize, int* returnSize) {
    int* pRetVal = NULL;

    int i, j;
    int node;

    int indegree[graphSize];
    memset(indegree, 0, sizeof(indegree));
    int adjacency[graphSize][1000];            // Boundary Test: Fail; AddressSanitizer:DEADLYSIGNAL
    memset(adjacency, -1, sizeof(adjacency));  // 0 <= graph[i][j] <= n - 1
    int adjacencyColSize[graphSize];
    memset(adjacencyColSize, 0, sizeof(adjacencyColSize));
    for (i = 0; i < graphSize; ++i) {
        for (j = 0; j < graphColSize[i]; ++j) {
            node = graph[i][j];
            adjacency[node][adjacencyColSize[node]++] = i;
            indegree[i]++;
        }
    }
#if (0)
    printf("indegree: ");
    for (i = 0; i < graphSize; ++i) {
        printf("%d ", indegree[i]);
    }
    printf("\n");
    for (i = 0; i < graphSize; ++i) {
        printf("adjacency[%d]: ", i);
        for (j = 0; j < graphSize; ++j) {
            printf("%2d ", adjacency[i][j]);
        }
        printf(": %d\n", adjacencyColSize[i]);
    }
#endif

#define MAX_QUEUE_SIZE ((graphSize)*2)
    int topologicalSortQueueHead = 0;
    int topologicalSortQueueTail = 0;
    int topologicalSortQueue[MAX_QUEUE_SIZE];
    for (i = 0; i < graphSize; i++) {
        if (indegree[i] == 0) {
            topologicalSortQueue[topologicalSortQueueTail++] = i;
        }
    }
#if (0)
    for (i = 0; i < (topologicalSortQueueTail - topologicalSortQueueHead); ++i) {
        printf("%d ", topologicalSortQueue[i]);
    }
    printf("\n");
#endif

    // Topological Sort Using Kahn's Algorithm
    bool safe[graphSize];
    for (i = 0; i < graphSize; i++) {
        safe[i] = false;
    }
    int neighbor;
    (*returnSize) = 0;
    while (topologicalSortQueueHead < topologicalSortQueueTail) {
        node = topologicalSortQueue[topologicalSortQueueHead++];
        if (safe[node] == false) {
            (*returnSize) += 1;
        }
        safe[node] = true;

        for (i = 0; i < adjacencyColSize[node]; ++i) {
            neighbor = adjacency[node][i];
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                topologicalSortQueue[topologicalSortQueueTail++] = neighbor;
            }
        }
    }

    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));
    (*returnSize) = 0;
    for (i = 0; i < graphSize; i++) {
        if (safe[i] == true) {
            pRetVal[(*returnSize)] = i;
            (*returnSize)++;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e3)
    struct testCaseType {
        int graph[MAX_SIZE][MAX_SIZE];
        int graphSize;
        int graphColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{{{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}}, 7, {2, 2, 1, 1, 1, 0, 0}, 0},
                    {{{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {}}, 5, {4, 2, 2, 2, 0}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
     *  Output: [2,4,5,6]
     *
     *  Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
     *  Output: [4]
     */

    int** pGraph = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: graph =  [");
        for (j = 0; j < testCase[i].graphSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].graphColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].graph[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pGraph = (int**)malloc(testCase[i].graphSize * sizeof(int*));
        if (pGraph == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].graphSize; ++j) {
            pGraph[j] = (int*)malloc(testCase[i].graphColSize[j] * sizeof(int));
            if (pGraph[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pGraph[k]) {
                        free(pGraph[k]);
                        pGraph[k] = NULL;
                    }
                }
                free(pGraph);
                pGraph = NULL;
                return EXIT_FAILURE;
            }
            memset(pGraph[j], 0, testCase[i].graphColSize[j] * sizeof(int));
            memcpy(pGraph[j], testCase[i].graph[j], testCase[i].graphColSize[j] * sizeof(int));
        }
        pAnswer = eventualSafeNodes(pGraph, testCase[i].graphSize, testCase[i].graphColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].graphSize; ++j) {
            if (pGraph[j]) {
                free(pGraph[j]);
                pGraph[j] = NULL;
            }
        }
        free(pGraph);
        pGraph = NULL;
    }

    return EXIT_SUCCESS;
}
