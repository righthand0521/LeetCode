#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    int data[1];
} Element;
typedef bool (*compare)(const void *, const void *);
typedef struct PriorityQueue {
    Element *arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;

Element *createElement(int x, int y) {
    Element *pObj = NULL;

    pObj = (Element *)malloc(sizeof(Element));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->data[0] = x;
    pObj->data[1] = y;

    return pObj;
}
static bool less(const void *a, const void *b) {
    bool retVal = false;

    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    retVal = (e1->data[0] > e2->data[0]);

    return retVal;
}
static bool greater(const void *a, const void *b) {
    bool retVal = false;

    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    retVal = (e1->data[0] < e2->data[0]);

    return retVal;
}
static void memswap(void *m1, void *m2, size_t size) {
    unsigned char *a = (unsigned char *)m1;
    unsigned char *b = (unsigned char *)m2;
    while (size--) {
        *b = *b ^ *a;
        *a = *b ^ *a;
        *b = *b ^ *a;
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
    bool retVal = (obj->queueSize == 0);

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

    return retVal;
}
void freeQueue(PriorityQueue *obj) {
    free(obj->arr);
    obj->arr = NULL;
    free(obj);
    obj = NULL;
}

#endif  // PRIORITY_QUEUE_H
long long minimumDifference(int *nums, int numsSize) {
    long long retVal = 0;

    int n = numsSize / 3;

    // max heap
    long long sum = 0;
    PriorityQueue *maxHeap = createPriorityQueue(greater);
    for (int i = 0; i < n; ++i) {
        sum += nums[i];
        Element e;
        e.data[0] = nums[i];
        enQueue(maxHeap, &e);
    }
    long long part1[n + 1];
    memset(part1, 0, sizeof(part1));
    part1[0] = sum;
    for (int i = n; i < n * 2; ++i) {
        sum += nums[i];
        Element e;
        e.data[0] = nums[i];
        enQueue(maxHeap, &e);
        sum -= front(maxHeap)->data[0];
        deQueue(maxHeap);
        part1[i - (n - 1)] = sum;
    }
    freeQueue(maxHeap);

    // min heap
    long long part2 = 0;
    PriorityQueue *minHeap = createPriorityQueue(less);
    for (int i = n * 3 - 1; i >= n * 2; --i) {
        part2 += nums[i];
        Element e;
        e.data[0] = nums[i];
        enQueue(minHeap, &e);
    }
    retVal = part1[n] - part2;
    for (int i = n * 2 - 1; i >= n; --i) {
        part2 += nums[i];
        Element e;
        e.data[0] = nums[i];
        enQueue(minHeap, &e);
        part2 -= front(minHeap)->data[0];
        deQueue(minHeap);
        retVal = fmin(retVal, part1[i - n] - part2);
    }
    freeQueue(minHeap);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(3 * 100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 1, 2}, 3}, {{7, 9, 5, 8, 1, 3}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,1,2]
     *  Output: -1
     *
     *  Input: nums = [7,9,5,8,1,3]
     *  Output: 1
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minimumDifference(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
