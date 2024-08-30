#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long *fromDestination = NULL;
long long *dijkstra(int op, int source, int n, int **edges, int edgesSize, int *edgesColSize, int **adjacency,
                    int *checkTarget) {
    long long *pRetVal = NULL;

    int i;

    pRetVal = (long long *)malloc(n * sizeof(long long));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (n * sizeof(long long)));
    for (i = 0; i < n; ++i) {
        pRetVal[i] = LLONG_MAX / 2;
    }
    pRetVal[source] = 0;

    bool visited[n];
    memset(visited, false, sizeof(visited));

    int u, v;
    int round;
    for (round = 0; round < n - 1; ++round) {
        u = -1;
        for (i = 0; i < n; ++i) {
            if (visited[i] == true) {
                continue;
            }

            if ((u == -1) || (pRetVal[i] < pRetVal[u])) {
                u = i;
            }
        }
        visited[u] = true;

        for (v = 0; v < n; ++v) {
            if (visited[v] == true) {
                continue;
            } else if (adjacency[u][v] == -1) {
                continue;
            }

            if (edges[adjacency[u][v]][2] != -1) {
                pRetVal[v] = fmin(pRetVal[v], pRetVal[u] + edges[adjacency[u][v]][2]);
                continue;
            }

            if (op == 0) {
                pRetVal[v] = fmin(pRetVal[v], pRetVal[u] + 1);
            } else {
                int modify = (*checkTarget) - pRetVal[u] - fromDestination[v];
                if (modify > 0) {
                    pRetVal[v] = fmin(pRetVal[v], pRetVal[u] + modify);
                    edges[adjacency[u][v]][2] = modify;
                } else {
                    edges[adjacency[u][v]][2] = (*checkTarget);
                }
            }
        }
    }

    return pRetVal;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **modifiedGraphEdges(int n, int **edges, int edgesSize, int *edgesColSize, int source, int destination, int target,
                         int *returnSize, int **returnColumnSizes) {
    int **pRetVal = NULL;

    (*returnSize) = 0;

    int i, j;

    int **adjacency = (int **)malloc(n * sizeof(int *));
    if (adjacency == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < n; ++i) {
        adjacency[i] = (int *)malloc(n * sizeof(int));
        if (adjacency[i] == NULL) {
            perror("malloc");
            goto exit_adjacency;
        }
        for (j = 0; j < n; ++j) {
            adjacency[i][j] = -1;
        }
    }
    for (i = 0; i < edgesSize; ++i) {
        adjacency[edges[i][0]][edges[i][1]] = i;
        adjacency[edges[i][1]][edges[i][0]] = i;
    }

    fromDestination = NULL;
    int checkTarget = target;
    fromDestination = dijkstra(0, destination, n, edges, edgesSize, edgesColSize, adjacency, &checkTarget);
    if (fromDestination == NULL) {
        perror("malloc");
        goto exit_adjacency;
    }
    if (fromDestination[source] > target) {
        goto exit_fromDestination;
    }

    long long *fromSource = dijkstra(1, source, n, edges, edgesSize, edgesColSize, adjacency, &checkTarget);
    if (fromDestination == NULL) {
        perror("malloc");
        goto exit_fromDestination;
    }
    if (fromSource[destination] != target) {
        goto exit_fromSource;
    }

    //
    pRetVal = edges;
    (*returnSize) = edgesSize;
    (*returnColumnSizes) = edgesColSize;

exit_fromSource:
    free(fromSource);
    fromSource = NULL;

exit_fromDestination:
    free(fromDestination);
    fromDestination = NULL;

exit_adjacency:
    for (i = 0; i < n; ++i) {
        if (adjacency[i] != NULL) {
            free(adjacency[i]);
            adjacency[i] = NULL;
        }
    }
    free(adjacency);
    adjacency = NULL;

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (100 * (100 - 1) / 2)
    struct testCaseType {
        int n;
        int edges[MAX_SIZE][3];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        int source;
        int destination;
        int target;
        int returnSize;
        int *returnColumnSizes;
    } testCase[] = {{5, {{4, 1, -1}, {2, 0, -1}, {0, 3, -1}, {4, 3, -1}}, 4, {3, 3, 3, 3}, 0, 1, 5, 0, NULL},
                    {3, {{0, 1, -1}, {0, 2, 5}}, 2, {3, 3}, 0, 2, 6, 0, NULL},
                    {4, {{1, 0, 4}, {1, 2, 3}, {2, 3, 5}, {0, 3, -1}}, 4, {3, 3, 3, 3}, 0, 2, 6, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0, destination = 1, target = 5
     *  Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
     *
     *  Input: n = 3, edges = [[0,1,-1],[0,2,5]], source = 0, destination = 2, target = 6
     *  Output: []
     *
     *  Input: n = 4, edges = [[1,0,4],[1,2,3],[2,3,5],[0,3,-1]], source = 0, destination = 2, target = 6
     *  Output: [[1,0,4],[1,2,3],[2,3,5],[0,3,1]]
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
        printf("], source = %d, destination = %d, target = %d\n", testCase[i].source, testCase[i].destination,
               testCase[i].target);

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
        pAnswer = modifiedGraphEdges(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize,
                                     testCase[i].source, testCase[i].destination, testCase[i].target,
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

        // free(testCase[i].returnColumnSizes);
        // testCase[i].returnColumnSizes = NULL;
        // for (j = 0; j < testCase[i].returnSize; ++j) {
        //     free(pAnswer[j]);
        //     pAnswer[j] = NULL;
        // }
        // free(pAnswer);
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
