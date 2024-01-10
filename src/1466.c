#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AdjacentNode {
    int val;
    struct AdjacentNode* next;
};
int minReorder(int n, int** connections, int connectionsSize, int* connectionsColSize) {
    int retVal = 0;

    int i, j;
    struct AdjacentNode* pCurrent = NULL;
    struct AdjacentNode* pTemp = NULL;

    // Build Adjacent Array
    struct AdjacentNode* adjacent[n];
    struct AdjacentNode* backAdjacent[n];
    for (i = 0; i < n; ++i) {
        adjacent[i] = (struct AdjacentNode*)malloc(sizeof(struct AdjacentNode));
        if (adjacent[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                pCurrent = adjacent[j];
                while (pCurrent != NULL) {
                    pTemp = pCurrent;
                    pCurrent = pCurrent->next;
                    free(pTemp);
                    pTemp = NULL;
                }
                pCurrent = backAdjacent[j];
                while (pCurrent != NULL) {
                    pTemp = pCurrent;
                    pCurrent = pCurrent->next;
                    free(pTemp);
                    pTemp = NULL;
                }
            }
            return retVal;
        }
        adjacent[i]->val = 0;
        adjacent[i]->next = NULL;
        backAdjacent[i] = (struct AdjacentNode*)malloc(sizeof(struct AdjacentNode));
        if (backAdjacent[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                pCurrent = adjacent[j];
                while (pCurrent != NULL) {
                    pTemp = pCurrent;
                    pCurrent = pCurrent->next;
                    free(pTemp);
                    pTemp = NULL;
                }
                pCurrent = backAdjacent[j];
                while (pCurrent != NULL) {
                    pTemp = pCurrent;
                    pCurrent = pCurrent->next;
                    free(pTemp);
                    pTemp = NULL;
                }
            }
            return retVal;
        }
        backAdjacent[i]->val = 0;
        backAdjacent[i]->next = NULL;
    }
    for (i = 0; i < connectionsSize; ++i) {
        pTemp = (struct AdjacentNode*)malloc(sizeof(struct AdjacentNode));
        if (pTemp == NULL) {
            perror("malloc");
            for (i = 0; i < n; ++i) {
                pCurrent = adjacent[i];
                while (pCurrent != NULL) {
                    pTemp = pCurrent;
                    pCurrent = pCurrent->next;
                    free(pTemp);
                    pTemp = NULL;
                }
                pCurrent = backAdjacent[i];
                while (pCurrent != NULL) {
                    pTemp = pCurrent;
                    pCurrent = pCurrent->next;
                    free(pTemp);
                    pTemp = NULL;
                }
            }
            return retVal;
        }
        pTemp->val = connections[i][1];
        pTemp->next = NULL;
        pCurrent = adjacent[connections[i][0]];
        while (pCurrent->next != NULL) {
            pCurrent = pCurrent->next;
        }
        pCurrent->next = pTemp;

        pTemp = (struct AdjacentNode*)malloc(sizeof(struct AdjacentNode));
        if (pTemp == NULL) {
            perror("malloc");
            for (i = 0; i < n; ++i) {
                pCurrent = adjacent[i];
                while (pCurrent != NULL) {
                    pTemp = pCurrent;
                    pCurrent = pCurrent->next;
                    free(pTemp);
                    pTemp = NULL;
                }
                pCurrent = backAdjacent[i];
                while (pCurrent != NULL) {
                    pTemp = pCurrent;
                    pCurrent = pCurrent->next;
                    free(pTemp);
                    pTemp = NULL;
                }
            }
            return retVal;
        }
        pTemp->val = connections[i][0];
        pTemp->next = NULL;
        pCurrent = backAdjacent[connections[i][1]];
        while (pCurrent->next != NULL) {
            pCurrent = pCurrent->next;
        }
        pCurrent->next = pTemp;
    }
    for (i = 0; i < n; ++i) {
        pCurrent = adjacent[i];
        adjacent[i] = adjacent[i]->next;
        free(pCurrent);
        pCurrent = NULL;

        pCurrent = backAdjacent[i];
        backAdjacent[i] = backAdjacent[i]->next;
        free(pCurrent);
        pCurrent = NULL;
    }

    // Breadth-First Search
    int bfsQueueFront = 0;
    int bfsQueueRear = 0;
    int bfsQueue[n * 2];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    bfsQueue[bfsQueueRear] = 0;
    ++bfsQueueRear;

    bool visit[n];
    memset(visit, false, sizeof(visit));

    int src;
    while (bfsQueueFront < bfsQueueRear) {
        src = bfsQueue[bfsQueueFront];
        ++bfsQueueFront;

        visit[src] = true;

        pCurrent = adjacent[src];
        while (pCurrent != NULL) {
            if (visit[pCurrent->val] == false) {
                ++retVal;
                bfsQueue[bfsQueueRear] = pCurrent->val;
                ++bfsQueueRear;
            }

            pCurrent = pCurrent->next;
        }
        pCurrent = backAdjacent[src];
        while (pCurrent != NULL) {
            if (visit[pCurrent->val] == false) {
                bfsQueue[bfsQueueRear] = pCurrent->val;
                ++bfsQueueRear;
            }

            pCurrent = pCurrent->next;
        }
    }

    // Free Adjacent Array
    for (i = 0; i < n; ++i) {
        pCurrent = adjacent[i];
        while (pCurrent != NULL) {
            pTemp = pCurrent;
            pCurrent = pCurrent->next;
            free(pTemp);
            pTemp = NULL;
        }
        pCurrent = backAdjacent[i];
        while (pCurrent != NULL) {
            pTemp = pCurrent;
            pCurrent = pCurrent->next;
            free(pTemp);
            pTemp = NULL;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50000)
    struct testCaseType {
        int n;
        int connections[MAX_SIZE][2];
        int connectionsSize;
        int connectionsColSize[MAX_SIZE];
    } testCase[] = {{6, {{0, 1}, {1, 3}, {2, 3}, {4, 0}, {4, 5}}, 5, {2, 2, 2, 2, 2}},
                    {5, {{1, 0}, {1, 2}, {3, 2}, {3, 4}}, 4, {2, 2, 2, 2}},
                    {3, {{1, 0}, {2, 0}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
     *  Output: 3
     *
     *  Input: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
     *  Output: 2
     *
     *  Input: n = 3, connections = [[1,0],[2,0]]
     *  Output: 0
     */

    int** pConnections = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, connections = [", testCase[i].n);
        for (j = 0; j < testCase[i].connectionsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].connectionsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].connections[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pConnections = (int**)malloc(testCase[i].connectionsSize * sizeof(int*));
        if (pConnections == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].connectionsSize; ++j) {
            pConnections[j] = (int*)malloc(testCase[i].connectionsColSize[j] * sizeof(int));
            if (pConnections[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pConnections[k]);
                }
                free(pConnections);
                return EXIT_FAILURE;
            }
            memset(pConnections[j], 0, (testCase[i].connectionsColSize[j] * sizeof(int)));
            memcpy(pConnections[j], testCase[i].connections[j], (testCase[i].connectionsColSize[j] * sizeof(int)));
        }

        answer = minReorder(testCase[i].n, pConnections, testCase[i].connectionsSize, testCase[i].connectionsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].connectionsSize; ++j) {
            free(pConnections[j]);
            pConnections[j] = NULL;
        }
        free(pConnections);
        pConnections = NULL;
    }

    return EXIT_SUCCESS;
}
