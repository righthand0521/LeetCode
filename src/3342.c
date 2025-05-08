#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef QUEUE_H
#define QUEUE_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    int x;
    int y;
    int distance;
} Element;
typedef bool (*compare)(const void *, const void *);
typedef struct PriorityQueue {
    Element *arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;

static bool greater(const void *a, const void *b) {
    static bool retVal = false;

    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    retVal = e1->distance > e2->distance;

    return retVal;
}
static void memswap(void *m1, void *m2, size_t size) {
    int tmp;
    unsigned char *a = (unsigned char *)m1;
    unsigned char *b = (unsigned char *)m2;
    while (size--) {
        tmp = *a;
        *a = *b;
        *b = tmp;

        a++;
        b++;
    }
}
static void swap(Element *arr, int i, int j) {
    //
    memswap(&arr[i], &arr[j], sizeof(Element));
}
static void down(Element *arr, int size, int i, compare cmpFunc) {
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
PriorityQueue *createPriorityQueue(compare cmpFunc) {
    PriorityQueue *obj = NULL;

    obj = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->capacity = MIN_QUEUE_SIZE;
    obj->arr = (Element *)malloc(sizeof(Element) * obj->capacity);
    if (obj->arr == NULL) {
        perror("malloc");
        free(obj);
        obj = NULL;
        return obj;
    }
    obj->queueSize = 0;
    obj->lessFunc = cmpFunc;

    return obj;
}
void heapfiy(PriorityQueue *obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->lessFunc);
    }
}
void enQueue(PriorityQueue *obj, Element *e) {
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
Element *deQueue(PriorityQueue *obj) {
    Element *pRetVal = NULL;

    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->lessFunc);
    pRetVal = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;

    return pRetVal;
}
bool isEmpty(const PriorityQueue *obj) {
    bool retVal = false;

    if (obj->queueSize == 0) {
        retVal = true;
    }

    return retVal;
}
Element *front(const PriorityQueue *obj) {
    Element *pRetVal = NULL;

    if (obj->queueSize == 0) {
        return NULL;
    }
    pRetVal = &obj->arr[0];

    return pRetVal;
}
void clear(PriorityQueue *obj) {
    //
    obj->queueSize = 0;
}
int size(const PriorityQueue *obj) {
    int retVal = obj->queueSize;

    return retVal;
}
void freeQueue(PriorityQueue *obj) {
    free(obj->arr);
    obj->arr = NULL;
    free(obj);
    obj = NULL;
}

#endif  // QUEUE_H
int minTimeToReach(int **moveTime, int moveTimeSize, int *moveTimeColSize) {
    int retVal = 0;

    int rowSize = moveTimeSize;
    int colSize = moveTimeColSize[0];

    int dijkstra[rowSize][colSize];
    memset(dijkstra, 0x3f, sizeof(dijkstra));
    dijkstra[0][0] = 0;

    int visit[rowSize][colSize];
    memset(visit, 0, sizeof(visit));

    PriorityQueue *queue = createPriorityQueue(greater);
    Element e = {0, 0, 0};
    enQueue(queue, &e);

    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    Element *p;
    Element s;
    int nextX, nextY, distances;
    while (isEmpty(queue) == false) {
        p = front(queue);
        s = (Element){p->x, p->y, p->distance};
        deQueue(queue);

        if (visit[s.x][s.y]) {
            continue;
        }

        if ((s.x == rowSize - 1) && (s.y == colSize - 1)) {
            break;
        }

        visit[s.x][s.y] = 1;

        for (int i = 0; i < 4; i++) {
            nextX = s.x + directions[i][0];
            if ((nextX < 0) || (nextX >= rowSize)) {
                continue;
            }
            nextY = s.y + directions[i][1];
            if ((nextY < 0) || (nextY >= colSize)) {
                continue;
            }

            distances = fmax(dijkstra[s.x][s.y], moveTime[nextX][nextY]) + (s.x + s.y) % 2 + 1;
            if (dijkstra[nextX][nextY] > distances) {
                dijkstra[nextX][nextY] = distances;
                e.x = nextX;
                e.y = nextY;
                e.distance = distances;
                enQueue(queue, &e);
            }
        }
    }
    retVal = dijkstra[rowSize - 1][colSize - 1];

    // Free the allocated memory
    freeQueue(queue);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (750)
    struct testCaseType {
        int moveTime[MAX_SIZE][MAX_SIZE];
        int moveTimeSize;
        int moveTimeColSize[MAX_SIZE];
    } testCase[] = {
        {{{0, 4}, {4, 4}}, 2, {2, 2}}, {{{0, 0, 0, 0}, {0, 0, 0, 0}}, 2, {4, 4}}, {{{0, 1}, {1, 2}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: moveTime = [[0,4],[4,4]]
     *  Output: 7
     *
     *  Input: moveTime = [[0,0,0,0],[0,0,0,0]]
     *  Output: 6
     *
     *  Input: moveTime = [[0,1],[1,2]]
     *  Output: 4
     */

    int **pMoveTime = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("moveTime = [");
        for (j = 0; j < testCase[i].moveTimeSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].moveTimeColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].moveTime[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pMoveTime = (int **)malloc(testCase[i].moveTimeSize * sizeof(int *));
        if (pMoveTime == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pMoveTime, 0, testCase[i].moveTimeSize * sizeof(int *));
        for (j = 0; j < testCase[i].moveTimeSize; ++j) {
            pMoveTime[j] = (int *)malloc(testCase[i].moveTimeColSize[j] * sizeof(int));
            if (pMoveTime[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pMoveTime[k]);
                    pMoveTime[k] = NULL;
                }
                free(pMoveTime);
                pMoveTime = NULL;
            }
            memset(pMoveTime[j], 0, (testCase[i].moveTimeColSize[j] * sizeof(int)));
            memcpy(pMoveTime[j], testCase[i].moveTime[j], (testCase[i].moveTimeColSize[j] * sizeof(int)));
        }
        answer = minTimeToReach(pMoveTime, testCase[i].moveTimeSize, testCase[i].moveTimeColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].moveTimeSize; ++j) {
            free(pMoveTime[j]);
            pMoveTime[j] = NULL;
        }
        free(pMoveTime);
        pMoveTime = NULL;
    }

    return EXIT_SUCCESS;
}
