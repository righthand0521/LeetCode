#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DFS (0)
#define BFS (1)
#if (DFS)
void dfs(int i, int** isConnected, int isConnectedSize, int* visited) {
    int j;
    for (j = 0; j < isConnectedSize; ++j) {
        if (isConnected[i][j] == 0) {
            continue;
        } else if (visited[j] == 1) {
            continue;
        } else {
            visited[j] = 1;
            dfs(j, isConnected, isConnectedSize, visited);
        }
    }
}
#elif (BFS)
void bfs(int i, int** isConnected, int isConnectedSize, int* visited) {
    visited[i] = 1;

    int bfsQueue[isConnectedSize * isConnectedSize];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueHead++] = i;

    int j;
    int idx;
    while (bfsQueueHead > bfsQueueTail) {
        idx = bfsQueue[bfsQueueTail];
        ++bfsQueueTail;
        for (j = 0; j < isConnectedSize; ++j) {
            if (isConnected[idx][j] == 0) {
                continue;
            } else if (visited[j] == 1) {
                continue;
            } else {
                visited[j] = 1;
                bfsQueue[bfsQueueHead++] = j;
            }
        }
    }
}
#endif
int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize) {
    int retVal = 0;

    int visited[isConnectedSize];
    memset(visited, 0, sizeof(visited));
    int i;
    for (i = 0; i < isConnectedSize; ++i) {
        if (visited[i] == 1) {
            continue;
        }

#if (DFS)
        printf("Depth-First Search\n\n");
        dfs(i, isConnected, isConnectedSize, visited);
#elif (BFS)
        printf("Breadth-First Search\n\n");
        bfs(i, isConnected, isConnectedSize, visited);
#endif

        ++retVal;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int isConnected[MAX_SIZE][MAX_SIZE];
        int isConnectedSize;
        int isConnectedColSize[MAX_SIZE];
    } testCase[] = {{{{1, 1, 0}, {1, 1, 0}, {0, 0, 1}}, 3, {3, 3, 3}},
                    {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
     *  Output: 2
     *
     *  Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
     *  Output: 3
     */

    int** pIsConnected = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: isConnected = [");
        for (j = 0; j < testCase[i].isConnectedSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", "[");
            for (k = 0; k < testCase[i].isConnectedColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].isConnected[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pIsConnected = (int**)malloc(testCase[i].isConnectedSize * sizeof(int*));
        if (pIsConnected == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].isConnectedSize; ++j) {
            pIsConnected[j] = (int*)malloc(testCase[i].isConnectedColSize[j] * sizeof(int));
            if (pIsConnected[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pIsConnected[k]);
                    pIsConnected[k] = NULL;
                }
                free(pIsConnected);
                pIsConnected = NULL;
                return EXIT_FAILURE;
            }
            memset(pIsConnected[j], 0, (testCase[i].isConnectedColSize[j] * sizeof(int)));
            memcpy(pIsConnected[j], testCase[i].isConnected[j], (testCase[i].isConnectedColSize[j] * sizeof(int)));
        }
        answer = findCircleNum(pIsConnected, testCase[i].isConnectedSize, testCase[i].isConnectedColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].isConnectedSize; ++j) {
            free(pIsConnected[j]);
            pIsConnected[j] = NULL;
        }
        free(pIsConnected);
        pIsConnected = NULL;
    }

    return EXIT_SUCCESS;
}
