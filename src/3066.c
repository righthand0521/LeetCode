#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HEAP_H
#define HEAP_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    long long data[1];
} Element;
typedef bool (*compare)(const void *, const void *);

typedef struct PriorityQueue {
    Element *arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;
Element *createElement(int x, int y) {
    Element *obj = (Element *)malloc(sizeof(Element));
    obj->data[0] = x;
    obj->data[1] = y;
    return obj;
}
static bool less(const void *a, const void *b) {
    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    return e1->data[0] > e2->data[0];
}
static void memswap(void *m1, void *m2, size_t size) {
    unsigned char *a = (unsigned char *)m1;
    unsigned char *b = (unsigned char *)m2;
    while (size--) {
        *b ^= *a ^= *b ^= *a;
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
    PriorityQueue *obj = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    obj->capacity = MIN_QUEUE_SIZE;
    obj->arr = (Element *)malloc(sizeof(Element) * obj->capacity);
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
    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->lessFunc);
    Element *e = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;
    return e;
}
bool isEmpty(const PriorityQueue *obj) {
    //
    return obj->queueSize == 0;
}
Element *front(const PriorityQueue *obj) {
    if (obj->queueSize == 0) {
        return NULL;
    } else {
        return &obj->arr[0];
    }
}
void clear(PriorityQueue *obj) {
    //
    obj->queueSize = 0;
}
int size(const PriorityQueue *obj) {
    //
    return obj->queueSize;
}
void freeQueue(PriorityQueue *obj) {
    free(obj->arr);
    free(obj);
}

#endif  // HEAP_H
int minOperations(int *nums, int numsSize, int k) {
    int retVal = 0;

    PriorityQueue *pMinHeap = createPriorityQueue(less);
    struct Element e;
    for (int i = 0; i < numsSize; i++) {
        e.data[0] = nums[i];
        enQueue(pMinHeap, &e);
    }

    long long x, y;
    while (front(pMinHeap)->data[0] < k) {
        x = front(pMinHeap)->data[0];
        deQueue(pMinHeap);
        y = front(pMinHeap)->data[0];
        deQueue(pMinHeap);
        e.data[0] = x + x + y;
        enQueue(pMinHeap, &e);

        retVal++;
    }

    //
    freeQueue(pMinHeap);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(2 * 100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{2, 11, 10, 1, 3}, 5, 10}, {{1, 1, 2, 4, 9}, 5, 20}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,11,10,1,3], k = 10
     *  Output: 2
     *
     *  Input: nums = [1,1,2,4,9], k = 20
     *  Output: 4
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = minOperations(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
