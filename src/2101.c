#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DFS (0)
#define BFS (1)
int bfs(int node, int** edges, int* edgesColSize, int bombsSize) {
    int retVal = 0;

    int visited[bombsSize];
    memset(visited, 0, sizeof(visited));
    visited[node] = 1;
    int bfsQueue[bombsSize * bombsSize];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueHead++] = node;
    ++retVal;

    int i;
    int current;
    while (bfsQueueHead > bfsQueueTail) {
        current = bfsQueue[bfsQueueTail];
        ++bfsQueueTail;
        for (i = 0; i < edgesColSize[current]; ++i) {
            if (visited[edges[current][i]] == 1) {
                continue;
            }
            visited[edges[current][i]] = 1;
            bfsQueue[bfsQueueHead++] = edges[current][i];
            ++retVal;
        }
    }

    return retVal;
}
int maximumDetonation(int** bombs, int bombsSize, int* bombsColSize) {
    int retVal = 0;

    int i, j;

    //
    int** edges = (int**)malloc(bombsSize * sizeof(int*));
    if (edges == NULL) {
        perror("malloc");
        return retVal;
    }
    for (i = 0; i < bombsSize; ++i) {
        edges[i] = (int*)malloc(bombsSize * sizeof(int));
        if (edges[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(edges[j]);
                edges[j] = NULL;
            }
            free(edges);
            edges = NULL;
            return retVal;
        }
        memset(edges[i], 0, (bombsSize * sizeof(int)));
    }
    int edgesColSize[bombsSize];
    memset(edgesColSize, 0, sizeof(edgesColSize));
    for (i = 0; i < bombsSize; ++i) {
        for (j = 0; j < bombsSize; ++j) {
            if (i == j) {
                continue;
            }

            // 1 <= xi, yi, ri <= 10^5
            long long dx = bombs[i][0] - bombs[j][0];
            long long dy = bombs[i][1] - bombs[j][1];
            long long dr = (dx * dx) + (dy * dy);
            long long r = (long long)bombs[i][2] * (long long)bombs[i][2];
            if (r >= dr) {
                edges[i][edgesColSize[i]++] = j;
            }
        }
    }
#if 0  // graph print
    for (i = 0; i < bombsSize; ++i) {
        printf("%d: ", i);
        for (j = 0; j < bombsSize; ++j) {
            printf("%d ", edges[i][j]);
        }
        printf(" => %d\n", edgesColSize[i]);
    }
#endif

    //
    for (int i = 0; i < bombsSize; ++i) {
#if (DFS)
#elif (BFS)
        retVal = fmax(retVal, bfs(i, edges, edgesColSize, bombsSize));
#endif
    }

    //
    for (i = 0; i < bombsSize; ++i) {
        free(edges[i]);
        edges[i] = NULL;
    }
    free(edges);
    edges = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int bombs[MAX_SIZE][3];
        int bombsSize;
        int bombsColSize[MAX_SIZE];
    } testCase[] = {{{{2, 1, 3}, {6, 1, 4}}, 2, {3, 3}},
                    {{{1, 1, 5}, {10, 10, 5}}, 2, {3, 3}},
                    {{{1, 2, 3}, {2, 3, 1}, {3, 4, 2}, {4, 5, 3}, {5, 6, 4}}, 5, {3, 3, 3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: bombs = [[2,1,3],[6,1,4]]
     *  Output: 2
     *
     *  Input: bombs = [[1,1,5],[10,10,5]]
     *  Output: 1
     *
     *  Input: bombs = [[1,2,3],[2,3,1],[3,4,2],[4,5,3],[5,6,4]]
     *  Output: 5
     */

    int** pBombs = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: bombs = [");
        for (j = 0; j < testCase[i].bombsSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", "[");
            for (k = 0; k < testCase[i].bombsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].bombs[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pBombs = (int**)malloc(testCase[i].bombsSize * sizeof(int*));
        if (pBombs == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].bombsSize; ++j) {
            pBombs[j] = (int*)malloc(testCase[i].bombsColSize[j] * sizeof(int));
            if (pBombs[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pBombs[k]);
                    pBombs[k] = NULL;
                }
                free(pBombs);
                pBombs = NULL;
                return EXIT_FAILURE;
            }
            memset(pBombs[j], 0, (testCase[i].bombsColSize[j] * sizeof(int)));
            memcpy(pBombs[j], testCase[i].bombs[j], (testCase[i].bombsColSize[j] * sizeof(int)));
        }
        answer = maximumDetonation(pBombs, testCase[i].bombsSize, testCase[i].bombsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].bombsSize; ++j) {
            free(pBombs[j]);
            pBombs[j] = NULL;
        }
        free(pBombs);
        pBombs = NULL;
    }

    return EXIT_SUCCESS;
}
