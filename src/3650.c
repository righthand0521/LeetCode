#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    int data[2];
} Element;
typedef bool (*compare)(const void*, const void*);
typedef struct PriorityQueue {
    Element* arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;
Element* createElement(int x, int y) {
    Element* pObj = NULL;

    pObj = (Element*)malloc(sizeof(Element));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->data[0] = x;
    pObj->data[1] = y;

    return pObj;
}
static bool less(const void* a, const void* b) {
    bool retVal = false;

    Element* e1 = (Element*)a;
    Element* e2 = (Element*)b;
    retVal = e1->data[0] > e2->data[0];

    return retVal;
}
#if 0
static bool greater(const void* a, const void* b) {
    bool retVal = false;

    Element* e1 = (Element*)a;
    Element* e2 = (Element*)b;
    retVal = e1->data[0] < e2->data[0];

    return retVal;
}
#endif
static void memswap(void* m1, void* m2, size_t size) {
    unsigned char* a = (unsigned char*)m1;
    unsigned char* b = (unsigned char*)m2;
    while (size--) {
        *b ^= *a;
        *a ^= *b;
        *b ^= *a;
        a++;
        b++;
    }
}
static void swap(Element* arr, int i, int j) {
    //
    memswap(&arr[i], &arr[j], sizeof(Element));
}
static void down(Element* arr, int size, int i, compare cmpFunc) {
    for (int k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if (k + 1 < size && cmpFunc(&arr[k], &arr[k + 1])) {
            k++;
        }

        if (cmpFunc(&arr[k], &arr[(k - 1) / 2])) {
            break;
        }

        swap(arr, k, (k - 1) / 2);
    }
}
PriorityQueue* createPriorityQueue(compare cmpFunc) {
    PriorityQueue* pObj = NULL;

    pObj = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->capacity = MIN_QUEUE_SIZE;
    pObj->arr = (Element*)malloc(sizeof(Element) * pObj->capacity);
    pObj->queueSize = 0;
    pObj->lessFunc = cmpFunc;

    return pObj;
}
void heapfiy(PriorityQueue* obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->lessFunc);
    }
}
void enQueue(PriorityQueue* obj, Element* e) {
    // we need to alloc more space, just twice space size
    if (obj->queueSize == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = realloc(obj->arr, sizeof(Element) * obj->capacity);
    }
    memcpy(&obj->arr[obj->queueSize], e, sizeof(Element));

    for (int i = obj->queueSize; i > 0 && obj->lessFunc(&obj->arr[(i - 1) / 2], &obj->arr[i]); i = (i - 1) / 2) {
        swap(obj->arr, i, (i - 1) / 2);
    }
    obj->queueSize++;
}
Element* deQueue(PriorityQueue* obj) {
    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->lessFunc);
    Element* e = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;

    return e;
}
bool isEmpty(const PriorityQueue* obj) {
    bool retVal = (obj->queueSize == 0);

    return retVal;
}
Element* front(const PriorityQueue* obj) {
    Element* pRetVal = NULL;

    if (obj->queueSize != 0) {
        pRetVal = &obj->arr[0];
    }

    return pRetVal;
}
void clear(PriorityQueue* obj) {
    //
    obj->queueSize = 0;
}
int size(const PriorityQueue* obj) {
    int retVal = obj->queueSize;

    return retVal;
}
void freeQueue(PriorityQueue* obj) {
    free(obj->arr);
    obj->arr = NULL;
    free(obj);
    obj = NULL;
}

#endif  // PRIORITYQUEUE_H
#ifndef GRAPH_H
#define GRAPH_H

typedef struct AdjNode {
    int vertex;
    int weight;
    struct AdjNode* next;
} AdjNode;
typedef struct {
    AdjNode** lists;
    int n;
} Graph;
AdjNode* createAdjNode(int vertex, int weight) {
    AdjNode* pObj = NULL;

    pObj = (AdjNode*)malloc(sizeof(AdjNode));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->vertex = vertex;
    pObj->weight = weight;
    pObj->next = NULL;

    return pObj;
}
Graph* createGraph(int n) {
    Graph* pObj = NULL;

    pObj = (Graph*)malloc(sizeof(Graph));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->n = n;
    pObj->lists = (AdjNode**)malloc(n * sizeof(AdjNode*));
    for (int i = 0; i < n; i++) {
        pObj->lists[i] = NULL;
    }

    return pObj;
}
void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjNode* newNode = createAdjNode(dest, weight);
    if (newNode == NULL) {
        perror("createAdjNode");
        return;
    }
    newNode->next = graph->lists[src];
    graph->lists[src] = newNode;

    AdjNode* reverseNode = createAdjNode(src, 2 * weight);
    if (reverseNode == NULL) {
        perror("createAdjNode");
        return;
    }
    reverseNode->next = graph->lists[dest];
    graph->lists[dest] = reverseNode;
}
void freeGraph(Graph* graph) {
    if (graph == NULL) {
        return;
    }

    AdjNode *current, *temp;
    for (int i = 0; i < graph->n; i++) {
        current = graph->lists[i];
        while (current != NULL) {
            temp = current;
            current = current->next;
            free(temp);
            temp = NULL;
        }
    }
    free(graph->lists);
    graph->lists = NULL;
    free(graph);
    graph = NULL;
}

#endif  // GRAPH_H
int minCost(int n, int** edges, int edgesSize, int* edgesColSize) {
    int retVal = -1;

    Graph* adjacency = createGraph(n);
    int src, dest, weight;
    for (int i = 0; i < edgesSize; i++) {
        src = edges[i][0];
        dest = edges[i][1];
        weight = edges[i][2];
        addEdge(adjacency, src, dest, weight);
    }

    int* distance = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
    }
    distance[0] = 0;

    bool* visited = (bool*)calloc(n, sizeof(bool));

    PriorityQueue* heap = createPriorityQueue(less);
    Element startElem;
    startElem.data[0] = 0;
    startElem.data[1] = 0;
    enQueue(heap, &startElem);

    Element *current, newElem;
    int currentDistance, x, y, w;
    while (isEmpty(heap) != true) {
        current = front(heap);
        currentDistance = current->data[0];
        x = current->data[1];
        deQueue(heap);

        if (x == n - 1) {
            retVal = currentDistance;
            break;
        }

        if (visited[x] == true) {
            continue;
        }
        visited[x] = true;

        for (AdjNode* neighbor = adjacency->lists[x]; neighbor != NULL; neighbor = neighbor->next) {
            y = neighbor->vertex;
            w = neighbor->weight;
            if (currentDistance + w < distance[y]) {
                distance[y] = currentDistance + w;

                newElem.data[0] = distance[y];
                newElem.data[1] = y;
                enQueue(heap, &newElem);
            }
        }
    }

    //
    free(distance);
    free(visited);
    freeQueue(heap);
    freeGraph(adjacency);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int n;
        int edges[MAX_SIZE][3];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
    } testCase[] = {{4, {{0, 1, 3}, {3, 1, 1}, {2, 3, 4}, {0, 2, 2}}, 4, {3, 3, 3, 3}},
                    {4, {{0, 2, 1}, {2, 1, 1}, {1, 3, 1}, {2, 3, 3}}, 4, {3, 3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4, edges = [[0,1,3],[3,1,1],[2,3,4],[0,2,2]]
     *  Output: 5
     *
     *  Input: n = 4, edges = [[0,2,1],[2,1,1],[1,3,1],[2,3,3]]
     *  Output: 3
     */

    int** pEdges = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, edges = [", testCase[i].n);
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].edges[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pEdges = (int**)malloc(testCase[i].edgesSize * sizeof(int*));
        if (pEdges == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            pEdges[j] = (int*)malloc(testCase[i].edgesColSize[j] * sizeof(int));
            if (pEdges[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pEdges[k]);
                }
                free(pEdges);
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, (testCase[i].edgesColSize[j] * sizeof(int)));
            memcpy(pEdges[j], testCase[i].edges[j], (testCase[i].edgesColSize[j] * sizeof(int)));
        }

        answer = minCost(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize);
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
