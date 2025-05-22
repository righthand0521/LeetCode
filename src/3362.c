#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HEAP_H
#define HEAP_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    int data;
} Element;
typedef bool (*compare)(const void *, const void *);
typedef struct PriorityQueue {
    Element *arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;

#if (0)
static bool less(const void *a, const void *b) {
    bool retVal = false;

    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    retVal = (e1->data > e2->data);

    return retVal;
}
#endif
static bool greater(const void *a, const void *b) {
    bool retVal = false;

    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    retVal = (e1->data < e2->data);

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
        if ((k + 1 < size) && (cmpFunc(&arr[k], &arr[k + 1]))) {
            k++;
        }

        if (cmpFunc(&arr[k], &arr[(k - 1) / 2])) {
            break;
        }

        swap(arr, k, (k - 1) / 2);
    }
}
PriorityQueue *createPriorityQueue(compare cmpFunc) {
    PriorityQueue *pObj = NULL;

    pObj = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->capacity = MIN_QUEUE_SIZE;
    pObj->arr = (Element *)malloc(sizeof(Element) * pObj->capacity);
    if (pObj->arr == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->queueSize = 0;
    pObj->lessFunc = cmpFunc;

    return pObj;
}
void heapfiy(PriorityQueue *obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->lessFunc);
    }
}
void enQueue(PriorityQueue *obj, Element *e) {
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

    retVal = (obj->queueSize == 0);

    return retVal;
}
Element *front(const PriorityQueue *obj) {
    Element *pRetVal = NULL;

    if (obj->queueSize != 0) {
        pRetVal = &obj->arr[0];
    }

    return pRetVal;
}
void clear(PriorityQueue *obj) {
    //
    obj->queueSize = 0;
}
int size(const PriorityQueue *obj) {
    int retVal = obj->queueSize;

    //
    return retVal;
}
void freeQueue(PriorityQueue *obj) {
    free(obj->arr);
    obj->arr = NULL;
    free(obj);
    obj = NULL;
}

#endif  // HEAP_H
int compareIntArray(const void *a, const void *b) {
    int *p1 = *(int **)a;
    int *p2 = *(int **)b;

    // ascending order
    return (p1[0] > p2[0]);
}
int maxRemoval(int *nums, int numsSize, int **queries, int queriesSize, int *queriesColSize) {
    int retVal = -1;

    qsort(queries, queriesSize, sizeof(int *), compareIntArray);

    PriorityQueue *heap = createPriorityQueue(greater);

    int deltaArray[numsSize + 1];
    memset(deltaArray, 0, sizeof(deltaArray));
    int operations = 0;

    Element e;
    int end;
    int j = 0;
    for (int i = 0; i < numsSize; i++) {
        operations += deltaArray[i];

        while ((j < queriesSize) && (queries[j][0] == i)) {
            e = (Element){queries[j][1]};
            enQueue(heap, &e);
            j++;
        }

        while ((operations < nums[i]) && (isEmpty(heap) == false) && (front(heap)->data >= i)) {
            operations += 1;
            end = front(heap)->data;
            deQueue(heap);
            deltaArray[end + 1] -= 1;
        }

        if (operations < nums[i]) {
            freeQueue(heap);
            return retVal;
        }
    }
    retVal = size(heap);

    //
    freeQueue(heap);
    heap = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
    } testCase[] = {{{2, 0, 2}, 3, {{0, 2}, {0, 2}, {1, 1}}, 3, {2, 2, 2}},
                    {{1, 1, 1, 1}, 4, {{1, 3}, {0, 2}, {1, 3}, {1, 2}}, 4, {2, 2, 2, 2}},
                    {{1, 2, 3, 4}, 4, {{0, 3}}, 1, {2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]
     *  Output: 1
     *
     *  Input: nums = [1,1,1,1], queries = [[1,3],[0,2],[1,3],[1,2]]
     *  Output: 2
     *
     *  Input: nums = [1,2,3,4], queries = [[0,3]]
     *  Output: -1
     */

    int **pQueries = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], queries =  [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].queriesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].queries[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pQueries = (int **)malloc(testCase[i].queriesSize * sizeof(int *));
        if (pQueries == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (int *)malloc(testCase[i].queriesColSize[j] * sizeof(int));
            if (pQueries[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pQueries[k]) {
                        free(pQueries[k]);
                        pQueries[k] = NULL;
                    }
                }
                free(pQueries);
                pQueries = NULL;
                return EXIT_FAILURE;
            }
            memset(pQueries[j], 0, testCase[i].queriesColSize[j] * sizeof(int));
            memcpy(pQueries[j], testCase[i].queries[j], testCase[i].queriesColSize[j] * sizeof(int));
        }
        answer = maxRemoval(testCase[i].nums, testCase[i].numsSize, pQueries, testCase[i].queriesSize,
                            testCase[i].queriesColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].queriesSize; ++j) {
            if (pQueries[j]) {
                free(pQueries[j]);
                pQueries[j] = NULL;
            }
        }
        free(pQueries);
        pQueries = NULL;
    }

    return EXIT_SUCCESS;
}
