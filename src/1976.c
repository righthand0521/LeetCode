#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ADJACENCY_H
#define ADJACENCY_H

typedef struct Edge {
    int to;
    int cost;
    struct Edge *next;
} Edge;
Edge *createEdge(int to, int cost) {
    Edge *pObj = NULL;

    pObj = (Edge *)malloc(sizeof(Edge));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->to = to;
    pObj->cost = cost;
    pObj->next = NULL;

    return pObj;
}
void freeEdgeList(Edge *pList) {
    while (pList) {
        Edge *pFree = pList;
        pList = pList->next;
        free(pFree);
    }
}

#endif  // ADJACENCY_H
#ifndef HEAP_H
#define HEAP_H

typedef struct {
    long long first;
    int second;
} Node;
typedef bool (*cmp)(const void *, const void *);
typedef struct {
    Node *arr;
    int capacity;
    int queueSize;
    cmp compare;
} PriorityQueue;
Node *createNode(long long x, int y) {
    Node *obj = (Node *)malloc(sizeof(Node));
    obj->first = x;
    obj->second = y;
    return obj;
}
PriorityQueue *createPriorityQueue(int size, cmp compare) {
    PriorityQueue *obj = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    obj->arr = (Node *)malloc(sizeof(Node) * size);
    obj->queueSize = 0;
    obj->capacity = size;
    obj->compare = compare;
    return obj;
}
static void swap(Node *arr, int i, int j) {
    Node tmp;
    memcpy(&tmp, &arr[i], sizeof(Node));
    memcpy(&arr[i], &arr[j], sizeof(Node));
    memcpy(&arr[j], &tmp, sizeof(Node));
}
static void down(Node *arr, int size, int i, cmp compare) {
    for (int k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if (k + 1 < size && compare(&arr[k], &arr[k + 1])) {
            k++;
        }
        if (compare(&arr[k], &arr[(k - 1) / 2])) {
            break;
        }
        swap(arr, k, (k - 1) / 2);
    }
}
void Heapfiy(PriorityQueue *obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->compare);
    }
}
void Push(PriorityQueue *obj, Node *node) {
    memcpy(&obj->arr[obj->queueSize], node, sizeof(Node));
    for (int i = obj->queueSize; i > 0 && obj->compare(&obj->arr[(i - 1) / 2], &obj->arr[i]); i = (i - 1) / 2) {
        swap(obj->arr, i, (i - 1) / 2);
    }
    obj->queueSize++;
}
Node *Pop(PriorityQueue *obj) {
    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->compare);
    Node *ret = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;
    return ret;
}
bool isEmpty(PriorityQueue *obj) {
    //
    return obj->queueSize == 0;
}
Node *Top(PriorityQueue *obj) {
    if (obj->queueSize == 0) {
        return NULL;
    } else {
        return &obj->arr[obj->queueSize];
    }
}
void FreePriorityQueue(PriorityQueue *obj) {
    free(obj->arr);
    free(obj);
}
bool greater(const void *a, const void *b) {
    //
    return ((Node *)a)->first > ((Node *)b)->first;
}

#endif  // HEAP_H
#define MODULO (int)(1e9 + 7)
int countPaths(int n, int **roads, int roadsSize, int *roadsColSize) {
    int retVal = 0;

    // Build adjacency list
    Edge *adjacency[n];
    for (int i = 0; i < n; i++) {
        adjacency[i] = NULL;
    }
    for (int i = 0; i < roadsSize; i++) {
        int u = roads[i][0];
        int v = roads[i][1];
        int t = roads[i][2];

        Edge *eu = createEdge(v, t);
        eu->next = adjacency[u];
        adjacency[u] = eu;

        Edge *ev = createEdge(u, t);
        ev->next = adjacency[v];
        adjacency[v] = ev;
    }

    long long shortestTime[n];  // Store shortest time to each node
    long long pathCount[n];     // Number of ways to reach each node in shortest time
    for (int i = 0; i < n; i++) {
        shortestTime[i] = LLONG_MAX;
        pathCount[i] = 0;
    }
    shortestTime[0] = 0;  // Distance to source is 0
    pathCount[0] = 1;     // 1 way to reach node 0

    // Min-Heap (priority queue) for Dijkstra
    PriorityQueue *minHeap = createPriorityQueue(n, greater);
    Node node;  // {time, node}
    node.first = 0;
    node.second = 0;
    Push(minHeap, &node);

    while (isEmpty(minHeap) == false) {
        Node *pCurrent = Pop(minHeap);
        long long currTime = pCurrent->first;
        int currNode = pCurrent->second;

        // Skip outdated distances
        if (currTime > shortestTime[currNode]) {
            continue;
        }

        for (Edge *pEntry = adjacency[currNode]; pEntry != NULL; pEntry = pEntry->next) {
            int neighborNode = pEntry->to;
            int roadTime = pEntry->cost;

            // Found a new shortest path → Update shortest time and reset path count
            if (currTime + roadTime < shortestTime[neighborNode]) {
                shortestTime[neighborNode] = currTime + roadTime;
                pathCount[neighborNode] = pathCount[currNode];
                Node node;
                node.first = currTime + roadTime;
                node.second = neighborNode;
                Push(minHeap, &node);
            }  // Found another way with the same shortest time → Add to path count
            else if (currTime + roadTime == shortestTime[neighborNode]) {
                pathCount[neighborNode] = (pathCount[neighborNode] + pathCount[currNode]) % MODULO;
            }
        }
    }
    retVal = pathCount[n - 1];

    // Free memory
    FreePriorityQueue(minHeap);
    for (int i = 0; i < n; i++) {
        freeEdgeList(adjacency[i]);
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int n;
        int roads[MAX_SIZE][3];
        int roadsSize;
        int roadsColSize[MAX_SIZE];
    } testCase[] = {
        {7,
         {{0, 6, 7}, {0, 1, 2}, {1, 2, 3}, {1, 3, 3}, {6, 3, 3}, {3, 5, 1}, {6, 5, 1}, {2, 5, 1}, {0, 4, 5}, {4, 6, 2}},
         10,
         {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}},
        {2, {{1, 0, 10}}, 1, {3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
     *  Output: 4
     *
     *  Input: n = 2, roads = [[1,0,10]]
     *  Output: 1
     */

    int **pRoads = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, roads = [", testCase[i].n);
        for (j = 0; j < testCase[i].roadsSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].roadsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].roads[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pRoads = (int **)malloc(testCase[i].roadsSize * sizeof(int *));
        if (pRoads == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].roadsSize; ++j) {
            pRoads[j] = (int *)malloc(testCase[i].roadsColSize[j] * sizeof(int));
            if (pRoads[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pRoads[k]) {
                        free(pRoads[k]);
                        pRoads[k] = NULL;
                    }
                }
                free(pRoads);
                pRoads = NULL;
                return EXIT_FAILURE;
            }
            memset(pRoads[j], 0, testCase[i].roadsColSize[j] * sizeof(int));
            memcpy(pRoads[j], testCase[i].roads[j], testCase[i].roadsColSize[j] * sizeof(int));
        }
        answer = countPaths(testCase[i].n, pRoads, testCase[i].roadsSize, testCase[i].roadsColSize);

        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].roadsSize; ++j) {
            if (pRoads[j]) {
                free(pRoads[j]);
                pRoads[j] = NULL;
            }
        }
        free(pRoads);
        pRoads = NULL;
    }

    return EXIT_SUCCESS;
}
