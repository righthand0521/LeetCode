#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shortestPathLength(int** graph, int graphSize, int* graphColSize) {
    int retVal = 0;

    //
    struct Node {
        int id;
        int mask;
        int distance;
    } bfsQueue[graphSize * (1 << graphSize)];
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;

    int visited[graphSize][1 << graphSize];
    memset(visited, 0, sizeof(visited));

    int i;
    for (i = 0; i < graphSize; ++i) {
        bfsQueue[bfsQueueTail].id = i;
        bfsQueue[bfsQueueTail].mask = 1 << i;
        bfsQueue[bfsQueueTail].distance = 0;
        bfsQueueTail++;
        visited[i][1 << i] = true;
    }

    //
    int vertex, maskVertex, distance;
    int neighbor, maskNeighbor;
    while (bfsQueueHead < bfsQueueTail) {
        vertex = bfsQueue[bfsQueueHead].id;
        maskVertex = bfsQueue[bfsQueueHead].mask;
        distance = bfsQueue[bfsQueueHead].distance;
        bfsQueueHead++;
        if (maskVertex == (1 << graphSize) - 1) {
            retVal = distance;
            break;
        }

        for (i = 0; i < graphColSize[vertex]; i++) {
            neighbor = graph[vertex][i];
            maskNeighbor = maskVertex | (1 << neighbor);
            if (visited[neighbor][maskNeighbor] == false) {
                bfsQueue[bfsQueueTail].id = neighbor;
                bfsQueue[bfsQueueTail].mask = maskNeighbor;
                bfsQueue[bfsQueueTail].distance = distance + 1;
                bfsQueueTail++;
                visited[neighbor][maskNeighbor] = true;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (12)
    struct testCaseType {
        int graph[MAX_SIZE][MAX_SIZE];
        int graphSize;
        int graphColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2, 3}, {0}, {0}, {0}}, 4, {3, 1, 1, 1}},
                    {{{1}, {0, 2, 4}, {1, 3, 4}, {2}, {1, 2}}, 5, {1, 3, 3, 1, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: graph = [[1,2,3],[0],[0],[0]]
     *  Output: 4
     *
     *  Input: graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
     *  Output: 4
     */

    int** pGraph = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: graph = [");
        for (j = 0; j < testCase[i].graphSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].graphColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].graph[j][k]);
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
            memset(pGraph[j], 0, testCase[i].graphColSize[j] * sizeof(int));
            memcpy(pGraph[j], testCase[i].graph[j], testCase[i].graphColSize[j] * sizeof(int));
        }
        answer = shortestPathLength(pGraph, testCase[i].graphSize, testCase[i].graphColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].graphSize; ++j) {
            free(pGraph[j]);
        }
        free(pGraph);
        pGraph = NULL;
    }

    return EXIT_SUCCESS;
}
