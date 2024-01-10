#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* vetr;
    int vetr_num;
    int** vetr_edge;
} Graph;
Graph* graphCreate(int n, int** edges, int edgesSize, int* edgesColSize) {
    Graph* obj = (Graph*)malloc(sizeof(Graph));

    int i;

    obj->vetr = (int*)calloc(n, sizeof(int));
    for (i = 0; i < n; i++) {
        obj->vetr[i] = i;
    }

    obj->vetr_num = n;

    obj->vetr_edge = (int**)calloc(n, sizeof(int*));
    for (i = 0; i < n; i++) {
        obj->vetr_edge[i] = (int*)calloc(n, sizeof(int));
    }
    for (i = 0; i < edgesSize; i++) {
        obj->vetr_edge[edges[i][0]][edges[i][1]] = edges[i][2];
    }

    return obj;
}
void graphAddEdge(Graph* obj, int* edge, int edgeSize) {
    //
    obj->vetr_edge[edge[0]][edge[1]] = edge[2];
}
int graphShortestPath(Graph* obj, int node1, int node2) {
    int retVal = 0;

    int* path = (int*)calloc(obj->vetr_num, sizeof(int));
    int i;
    for (i = 0; i < obj->vetr_num; i++) {
        path[i] = -1;
    }

    int judge[obj->vetr_num];
    memset(judge, 0, sizeof(judge));
    path[node1] = 0;

    int node;
    int min[2];
    while (1) {
        min[0] = -1;
        min[1] = -1;

        for (node = 0; node < obj->vetr_num; node++) {
            if (path[node] != -1 && judge[node] == 0) {
                if (min[0] == -1) {
                    min[0] = node;
                    min[1] = path[node];
                } else {
                    if (min[1] > path[node]) {
                        min[0] = node;
                        min[1] = path[node];
                    }
                }
            }
        }

        if (min[0] != -1) {
            judge[min[0]] = 1;
            for (i = 0; i < obj->vetr_num; i++) {
                if ((obj->vetr_edge[min[0]][i] != 0) && (judge[i] == 0)) {
                    if (path[i] == -1) {
                        path[i] = path[min[0]] + obj->vetr_edge[min[0]][i];
                    } else {
                        node = path[min[0]] + obj->vetr_edge[min[0]][i];
                        path[i] = ((path[i] > node) ? (node) : (path[i]));
                    }
                }
            }
        } else {
            break;
        }
    }

    retVal = path[node2];

    free(path);
    path = NULL;

    return retVal;
}
void graphFree(Graph* obj) {
    int i;
    for (i = 0; i < obj->vetr_num; i++) {
        free(obj->vetr_edge[i]);
        obj->vetr_edge[i] = NULL;
    }
    free(obj->vetr_edge);
    obj->vetr_edge = NULL;

    free(obj->vetr);
    obj->vetr = NULL;

    free(obj);
    obj = NULL;
}
/**
 * Your Graph struct will be instantiated and called as such:
 * Graph* obj = graphCreate(n, edges, edgesSize, edgesColSize);
 * graphAddEdge(obj, edge, edgeSize);
 * int param_2 = graphShortestPath(obj, node1, node2);
 * graphFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int n[MAX_SIZE];
        int edges[MAX_SIZE][MAX_SIZE][3];
        int edgesSize[MAX_SIZE];
        int edgesColSize[MAX_SIZE][MAX_SIZE];
        int node1[MAX_SIZE];
        int node2[MAX_SIZE];

        int calls;
    } testCase[] = {{{"Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"},
                     {4, 0, 0, 1, 0},
                     {{{0, 2, 5}, {0, 1, 2}, {1, 2, 1}, {3, 0, 3}}, {}, {}, {{1, 3, 4}}, {}},
                     {4, 0, 0, 1, 0},
                     {{3, 3, 3, 3}, {}, {}, {3}, {}},
                     {0, 3, 0, 0, 0},
                     {0, 2, 3, 0, 3},
                     5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"]
     *  [[4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]], [3, 2], [0, 3], [[1, 3, 4]], [0, 3]]
     *  Output
     *  [null, 6, -1, null, 6]
     */

    Graph* obj = NULL;
    int** pEdges = NULL;
    int retInt;
    int i, j, k, l;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[", (j == 0) ? "" : ", ");
            if (strcmp(testCase[i].methods[j], "Graph") == 0) {
                printf("%d, [", testCase[i].n[j]);
                for (k = 0; k < testCase[i].edgesSize[j]; ++k) {
                    printf("%s[", (k == 0) ? "" : ", ");
                    for (l = 0; l < testCase[i].edgesColSize[j][k]; ++l) {
                        printf("%s%d", (l == 0) ? "" : ", ", testCase[i].edges[j][k][l]);
                    }
                    printf("]");
                }
                printf("]");
            } else if (strcmp(testCase[i].methods[j], "addEdge") == 0) {
                for (k = 0; k < testCase[i].edgesSize[j]; ++k) {
                    printf("%s[", (k == 0) ? "" : ", ");
                    for (l = 0; l < testCase[i].edgesColSize[j][k]; ++l) {
                        printf("%s%d", (l == 0) ? "" : ", ", testCase[i].edges[j][k][l]);
                    }
                    printf("]");
                }
            } else if (strcmp(testCase[i].methods[j], "shortestPath") == 0) {
                printf("%d, %d", testCase[i].node1[j], testCase[i].node2[j]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "Graph") == 0) {
                pEdges = (int**)calloc(testCase[i].edgesSize[j], sizeof(int*));
                for (k = 0; k < testCase[i].edgesSize[j]; ++k) {
                    pEdges[k] = (int*)calloc(testCase[i].edgesColSize[j][k], sizeof(int));
                    memcpy(pEdges[k], testCase[i].edges[j][k], (testCase[i].edgesColSize[j][k] * sizeof(int)));
                }
                obj = graphCreate(testCase[i].n[j], pEdges, testCase[i].edgesSize[j], testCase[i].edgesColSize[j]);
                printf("%snull", (j == 0) ? "" : ", ");

                for (k = 0; k < testCase[i].edgesSize[j]; ++k) {
                    free(pEdges[k]);
                    pEdges[k] = NULL;
                }
                free(pEdges);
                pEdges = NULL;
            } else if (strcmp(testCase[i].methods[j], "addEdge") == 0) {
                graphAddEdge(obj, testCase[i].edges[j][0], testCase[i].edgesSize[j]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "shortestPath") == 0) {
                retInt = graphShortestPath(obj, testCase[i].node1[j], testCase[i].node2[j]);
                printf("%s%d", (j == 0) ? "" : ", ", retInt);
            }
        }
        printf("]\n");

        graphFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
