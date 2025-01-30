#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UnionFind_H
#define UnionFind_H

void swap(int *a, int *b) {
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
int find(int node, int *parent) {
    int retVal = 0;

    while (parent[node] != -1) {
        node = parent[node];
    }
    retVal = node;

    return retVal;
}
void Union(int node1, int node2, int *parent, int *depth) {
    node1 = find(node1, parent);
    node2 = find(node2, parent);

    // If both nodes already belong to the same set, no action needed
    if (node1 == node2) {
        return;
    }

    // Union by rank (depth) to keep the tree balanced
    if (depth[node1] < depth[node2]) {
        swap(&node1, &node2);
    }
    parent[node2] = node1;

    // If the depths are equal, increment the depth of the new root
    if (depth[node1] == depth[node2]) {
        depth[node1]++;
    }
}

#endif  // UnionFind_H
int getNumberOfGroups(int **adjacencyList, int adjacencyListSize, int srcNode, int n) {
    int retVal = 0;

    // Perform BFS to calculate the number of layers (groups)
    int bfsQueueSize = n * n;
    int bfsQueue[bfsQueueSize];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueFront = 0;
    int bfsQueueRear = 0;
    bfsQueue[bfsQueueRear++] = srcNode;

    int layerSeen[n];
    for (int i = 0; i < n; ++i) {
        layerSeen[i] = -1;
    }
    layerSeen[srcNode] = 0;

    int bfsQueueCount, currentNode, neighbor;
    while (bfsQueueFront < bfsQueueRear) {
        bfsQueueCount = bfsQueueRear - bfsQueueFront;
        for (int i = 0; i < bfsQueueCount; i++) {
            currentNode = bfsQueue[bfsQueueFront++];

            for (int j = 0; j < adjacencyListSize; ++j) {
                neighbor = adjacencyList[currentNode][j];
                if (neighbor == -1) {
                    continue;
                }

                // If neighbor hasn't been visited, assign it to the next layer
                if (layerSeen[neighbor] == -1) {
                    layerSeen[neighbor] = retVal + 1;
                    bfsQueue[bfsQueueRear++] = neighbor;
                    continue;
                }

                // If the neighbor is already in the same layer, return -1 (invalid partition)
                if (layerSeen[neighbor] == retVal) {
                    retVal = -1;
                    return retVal;
                }
            }
        }
        retVal++;
    }

    return retVal;
}
int magnificentSets(int n, int **edges, int edgesSize, int *edgesColSize) {
    int retVal = 0;

    // Build the adjacency list and apply Union-Find for each edge
    int **adjacencyList = (int **)malloc(n * sizeof(int *));
    if (adjacencyList == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < n; ++i) {
        adjacencyList[i] = (int *)malloc(n * sizeof(int));
        if (adjacencyList[i] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; ++j) {
                free(adjacencyList[j]);
                adjacencyList[j] = NULL;
            }
            free(adjacencyList);
            adjacencyList = NULL;
            return retVal;
        }
        for (int j = 0; j < n; ++j) {
            adjacencyList[i][j] = -1;
        }
    }

    int *parent = (int *)malloc(n * sizeof(int));
    if (parent == NULL) {
        perror("malloc");
        for (int i = 0; i < n; ++i) {
            free(adjacencyList[i]);
            adjacencyList[i] = NULL;
        }
        free(adjacencyList);
        adjacencyList = NULL;
        return retVal;
    }

    int *depth = (int *)malloc(n * sizeof(int));
    if (depth == NULL) {
        perror("malloc");
        free(parent);
        parent = NULL;
        for (int i = 0; i < n; ++i) {
            free(adjacencyList[i]);
            adjacencyList[i] = NULL;
        }
        free(adjacencyList);
        adjacencyList = NULL;
        return retVal;
    }
    for (int i = 0; i < n; ++i) {
        parent[i] = -1;
        depth[i] = 0;
    }

    int src, dst;
    for (int i = 0; i < edgesSize; ++i) {
        src = edges[i][0] - 1;
        dst = edges[i][1] - 1;
        adjacencyList[src][dst] = dst;
        adjacencyList[dst][src] = src;
        Union(src, dst, parent, depth);
    }

    // For each node, calculate the maximum number of groups for its component
    int numOfGroupsForComponent[n];
    for (int i = 0; i < n; ++i) {
        numOfGroupsForComponent[i] = -1;
    }

    int numberOfGroups, rootNode;
    for (int node = 0; node < n; node++) {
        numberOfGroups = getNumberOfGroups(adjacencyList, n, node, n);
        if (numberOfGroups == -1) {
            retVal = -1;  // If invalid split, return -1
            break;
        }
        rootNode = find(node, parent);
        numOfGroupsForComponent[rootNode] = fmax(numOfGroupsForComponent[rootNode], numberOfGroups);
    }

    // Calculate the total number of groups across all components
    if (retVal != -1) {
        for (int i = 0; i < n; ++i) {
            if (numOfGroupsForComponent[i] == -1) {
                continue;
            }
            retVal += numOfGroupsForComponent[i];
        }
    }

    //
    free(depth);
    depth = NULL;
    free(parent);
    parent = NULL;
    for (int i = 0; i < n; ++i) {
        free(adjacencyList[i]);
        adjacencyList[i] = NULL;
    }
    free(adjacencyList);
    adjacencyList = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_ROW_SIZE (int)(1e4)
#define MAX_COL_SIZE (2)
    struct testCaseType {
        int n;
        int edges[MAX_ROW_SIZE][MAX_COL_SIZE];
        int edgesSize;
        int edgesColSize[MAX_ROW_SIZE];
    } testCase[] = {{6, {{1, 2}, {1, 4}, {1, 5}, {2, 6}, {2, 3}, {4, 6}}, 6, {2, 2, 2, 2, 2, 2}},
                    {3, {{1, 2}, {2, 3}, {3, 1}}, 3, {2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
     *  Output: 4
     *
     *  Input: n = 3, edges = [[1,2],[2,3],[3,1]]
     *  Output: -1
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
        answer = magnificentSets(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize);
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
