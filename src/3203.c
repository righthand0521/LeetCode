#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** buildAdjList(int** edges, int edgesSize, int* edgesColSize, int** returnColSize) {
    int** pRetVal = NULL;

    int returnSize = edgesSize + 1;

    (*returnColSize) = (int*)malloc(returnSize * sizeof(int));
    if ((*returnColSize) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColSize), 0, (returnSize * sizeof(int)));
    for (int i = 0; i < edgesSize; ++i) {
        (*returnColSize)[edges[i][0]]++;
        (*returnColSize)[edges[i][1]]++;
    }

    pRetVal = (int**)malloc(returnSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColSize));
        (*returnColSize) = NULL;
        return pRetVal;
    }
    for (int i = 0; i < returnSize; ++i) {
        pRetVal[i] = (int*)malloc((*returnColSize)[i] * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            free((*returnColSize));
            (*returnColSize) = NULL;
            for (int j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[i], 0, ((*returnColSize)[i] * sizeof(int)));
    }

    memset((*returnColSize), 0, (returnSize * sizeof(int)));
    int src, dst;
    for (int i = 0; i < edgesSize; ++i) {
        src = edges[i][0];
        dst = edges[i][1];
        pRetVal[src][(*returnColSize)[src]++] = dst;
        pRetVal[dst][(*returnColSize)[dst]++] = src;
    }

    return pRetVal;
};
void findDiameter(int** adjList, int* adjListColSize, int node, int parent, int* first, int* second) {
    (*first) = 0;
    (*second) = 0;

    int childDiameter, depth;
    int maxDepth1 = 0;
    int maxDepth2 = 0;
    int diameter = 0;
    for (int i = 0; i < adjListColSize[node]; ++i) {
        // Skip the parent to avoid cycles
        if (adjList[node][i] == parent) {
            continue;
        }

        // Recursively calculate the diameter and depth of the neighbor's subtree
        findDiameter(adjList, adjListColSize, adjList[node][i], node, first, second);
        childDiameter = (*first);
        depth = (*second);

        // Update the maximum diameter of the subtree
        diameter = fmax(diameter, childDiameter);

        // Increment the depth to include the edge to this neighbor
        depth++;

        // Update the two largest depths from the current node
        if (depth > maxDepth1) {
            maxDepth2 = maxDepth1;
            maxDepth1 = depth;
        } else if (depth > maxDepth2) {
            maxDepth2 = depth;
        }
    }

    // Update the diameter to include the path through the current node
    diameter = fmax(diameter, maxDepth1 + maxDepth2);

    (*first) = diameter;
    (*second) = maxDepth1;
}
int minimumDiameterAfterMerge(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size,
                              int* edges2ColSize) {
    int retVal = 0;

    int* adjListColSize1 = NULL;
    int** adjList1 = buildAdjList(edges1, edges1Size, edges1ColSize, &adjListColSize1);
    int diameter1 = 0;
    findDiameter(adjList1, adjListColSize1, 0, -1, &diameter1, &retVal);

    int* adjListColSize2 = NULL;
    int** adjList2 = buildAdjList(edges2, edges2Size, edges2ColSize, &adjListColSize2);
    int diameter2 = 0;
    findDiameter(adjList2, adjListColSize2, 0, -1, &diameter2, &retVal);

    int combinedDiameter = ceil(diameter1 / 2.0) + ceil(diameter2 / 2.0) + 1;

    retVal = diameter1;
    retVal = fmax(retVal, diameter2);
    retVal = fmax(retVal, combinedDiameter);

    //
    free(adjListColSize1);
    adjListColSize1 = NULL;
    for (int i = 0; i <= edges1Size; ++i) {
        free(adjList1[i]);
        adjList1[i] = NULL;
    }
    free(adjList1);
    adjList1 = NULL;
    free(adjListColSize2);
    adjListColSize2 = NULL;
    for (int i = 0; i <= edges2Size; ++i) {
        free(adjList2[i]);
        adjList2[i] = NULL;
    }
    free(adjList2);
    adjList2 = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int edges1[MAX_SIZE][2];
        int edges1Size;
        int edges1ColSize[MAX_SIZE];
        int edges2[MAX_SIZE][2];
        int edges2Size;
        int edges2ColSize[MAX_SIZE];
    } testCase[] = {{{{0, 1}, {0, 2}, {0, 3}}, 3, {2, 2, 2}, {{0, 1}}, 1, {2}},
                    {{{0, 1}, {0, 2}, {0, 3}, {2, 4}, {2, 5}, {3, 6}, {2, 7}},
                     7,
                     {2, 2, 2, 2, 2, 2, 2},
                     {{0, 1}, {0, 2}, {0, 3}, {2, 4}, {2, 5}, {3, 6}, {2, 7}},
                     7,
                     {2, 2, 2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
     *  Output: 3
     *
     *  Input: edges1=[[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]], edges2=[[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]
     *  Output: 5
     */

    int** pEdges1 = NULL;
    int** pEdges2 = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("edges1 = [");
        for (j = 0; j < testCase[i].edges1Size; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edges1ColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges1[j][k]);
            }
            printf("]");
        }
        printf("], edges2 = [");
        for (j = 0; j < testCase[i].edges2Size; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edges2ColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges2[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pEdges1 = (int**)malloc(testCase[i].edges1Size * sizeof(int*));
        if (pEdges1 == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edges1Size; ++j) {
            pEdges1[j] = (int*)malloc(testCase[i].edges1ColSize[j] * sizeof(int));
            if (pEdges1[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pEdges1[k]) {
                        free(pEdges1[k]);
                        pEdges1[k] = NULL;
                    }
                }
                free(pEdges1);
                pEdges1 = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges1[j], 0, testCase[i].edges1ColSize[j] * sizeof(int));
            memcpy(pEdges1[j], testCase[i].edges1[j], testCase[i].edges1ColSize[j] * sizeof(int));
        }

        pEdges2 = (int**)malloc(testCase[i].edges2Size * sizeof(int*));
        if (pEdges1 == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edges2Size; ++j) {
            pEdges2[j] = (int*)malloc(testCase[i].edges2ColSize[j] * sizeof(int));
            if (pEdges2[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pEdges2[k]) {
                        free(pEdges2[k]);
                        pEdges2[k] = NULL;
                    }
                }
                free(pEdges2);
                pEdges2 = NULL;
                for (j = 0; j < testCase[i].edges1Size; ++j) {
                    if (pEdges1[j]) {
                        free(pEdges1[j]);
                        pEdges1[j] = NULL;
                    }
                }
                free(pEdges1);
                pEdges1 = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges2[j], 0, testCase[i].edges2ColSize[j] * sizeof(int));
            memcpy(pEdges2[j], testCase[i].edges2[j], testCase[i].edges2ColSize[j] * sizeof(int));
        }

        answer = minimumDiameterAfterMerge(pEdges1, testCase[i].edges1Size, testCase[i].edges1ColSize, pEdges2,
                                           testCase[i].edges2Size, testCase[i].edges2ColSize);

        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].edges1Size; ++j) {
            if (pEdges1[j]) {
                free(pEdges1[j]);
                pEdges1[j] = NULL;
            }
        }
        free(pEdges1);
        pEdges1 = NULL;
        for (j = 0; j < testCase[i].edges2Size; ++j) {
            if (pEdges2[j]) {
                free(pEdges2[j]);
                pEdges2[j] = NULL;
            }
        }
        free(pEdges2);
        pEdges2 = NULL;
    }

    return EXIT_SUCCESS;
}
