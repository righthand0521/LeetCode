#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DFS (1)
#define BFS (1)
#if (DFS)
#define SETS_NONE (0)
#define SETS_A (1)
#define SETS_B (-1)
bool dfs(int node, int** graph, int graphSize, int* graphColSize, int* color, int colorSize) {
    bool retVal = true;

    int neighbor;
    int i;
    for (i = 0; i < graphColSize[node]; ++i) {
        neighbor = graph[node][i];
        if (color[neighbor] != SETS_NONE) {
            if (color[neighbor] == color[node]) {
                retVal = false;
                break;
            }
        } else {
            color[neighbor] = -color[node];
            retVal = dfs(neighbor, graph, graphSize, graphColSize, color, colorSize);
            if (retVal == false) {
                break;
            }
        }
    }

    return retVal;
}
#elif (BFS)
#endif
bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    bool retVal = true;

    int colorSize = graphSize;
    int color[colorSize];
    memset(color, SETS_NONE, sizeof(color));

    int node;
    for (node = 0; node < graphSize; ++node) {
        if (color[node] != SETS_NONE) {
            continue;
        }
        color[node] = SETS_A;

#if (DFS)
        printf("DFS\n");
        retVal = dfs(node, graph, graphSize, graphColSize, color, colorSize);
        if (retVal == false) {
            break;
        }
#elif (BFS)
        printf("BFS\n");
#endif
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int graph[MAX_SIZE][MAX_SIZE];
        int graphSize;
        int graphColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}}, 4, {3, 2, 3, 2}},
                    {{{1, 3}, {0, 2}, {1, 3}, {0, 2}}, 4, {2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
     *  Output: false
     *
     *  Input: graph = [[1,3],[0,2],[1,3],[0,2]]
     *  Output: true
     */

    int** pGraph = NULL;
    bool answer = false;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: graph = [");
        for (j = 0; j < testCase[i].graphSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", "[");
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
                    free(pGraph[k]);
                    pGraph[k] = NULL;
                }
                free(pGraph);
                pGraph = NULL;
                return EXIT_FAILURE;
            }
            memset(pGraph[j], 0, (testCase[i].graphColSize[j] * sizeof(int)));
            memcpy(pGraph[j], testCase[i].graph[j], (testCase[i].graphColSize[j] * sizeof(int)));
        }
        answer = isBipartite(pGraph, testCase[i].graphSize, testCase[i].graphColSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        for (j = 0; j < testCase[i].graphSize; ++j) {
            free(pGraph[j]);
            pGraph[j] = NULL;
        }
        free(pGraph);
        pGraph = NULL;
    }

    return EXIT_SUCCESS;
}
