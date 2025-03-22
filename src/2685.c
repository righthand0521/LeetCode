#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countCompleteComponents(int n, int** edges, int edgesSize, int* edgesColSize) {
    int retVal = 0;

    // Create adjacency list representation of the graph
    int adjacency[n][n];
    memset(adjacency, 0, (n * n * sizeof(int)));
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adjacency[u][v] = 1;
        adjacency[v][u] = 1;
    }

    bool visited[n];
    memset(visited, false, sizeof(visited));

    int component[n * n];
    int componentSize;
    int bfsQueue[n * n];
    int bfsQueueHead, bfsQueueTail, current;
    bool isComplete;
    int adjacencyNodeSize;
    for (int vertex = 0; vertex < n; vertex++) {
        if (visited[vertex] == true) {
            continue;
        }
        visited[vertex] = true;

        // BFS to find all vertices in the current component
        memset(component, 0, sizeof(component));
        componentSize = 0;
        memset(bfsQueue, 0, (n * n * sizeof(int)));
        bfsQueueHead = 0;
        bfsQueueTail = 0;
        bfsQueue[bfsQueueTail++] = vertex;
        while (bfsQueueHead < bfsQueueTail) {
            current = bfsQueue[bfsQueueHead++];
            component[componentSize++] = current;

            // Process neighbors
            for (int neighbor = 0; neighbor < n; neighbor++) {
                if (adjacency[current][neighbor] == 0) {
                    continue;
                }
                if (visited[neighbor] == true) {
                    continue;
                }
                bfsQueue[bfsQueueTail++] = neighbor;
                visited[neighbor] = true;
            }
        }

        // Check if component is complete(all vertices have the right number of edges)
        isComplete = true;
        for (int node = 0; node < componentSize; node++) {
            adjacencyNodeSize = 0;
            for (int neighbor = 0; neighbor < n; neighbor++) {
                if (adjacency[component[node]][neighbor] == 1) {
                    adjacencyNodeSize++;
                }
            }
            if (adjacencyNodeSize != componentSize - 1) {
                isComplete = false;
                break;
            }
        }
        if (isComplete == true) {
            retVal++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int n;
        int edges[MAX_SIZE][2];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
    } testCase[] = {{6, {{0, 1}, {0, 2}, {1, 2}, {3, 4}}, 4, {2, 2, 2, 2}},
                    {6, {{0, 1}, {0, 2}, {1, 2}, {3, 4}, {3, 5}}, 5, {2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
     *  Output: 3
     *
     *  Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[3,5]]
     *  Output: 1
     */

    int** pEdges = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, edges = [", testCase[i].n);
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].edges[j][k]);
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
                    free(pEdges[k]);
                }
                free(pEdges);
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, (testCase[i].edgesColSize[j] * sizeof(int)));
            memcpy(pEdges[j], testCase[i].edges[j], (testCase[i].edgesColSize[j] * sizeof(int)));
        }

        answer = countCompleteComponents(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize);
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
