#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HEAP_H
#define HEAP_H

#define MIN_QUEUE_SIZE (4096)
typedef struct Node {
    long long value;
    int left;
    struct Node* prev;
    struct Node* next;
} Node;
Node* createNode(long long value, int left) {
    Node* pObj = NULL;

    pObj = (Node*)malloc(sizeof(Node));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->value = value;
    pObj->left = left;
    pObj->prev = NULL;
    pObj->next = NULL;

    return pObj;
}
typedef struct QueueItem {
    Node* first;
    Node* second;
    long long cost;
    int firstLeft;
    int secondLeft;
} QueueItem;
typedef struct Element {
    QueueItem item;
} Element;
typedef bool (*CompareFunc)(const void*, const void*);
static bool itemLess(const void* a, const void* b) {
    bool retVal = false;

    const Element* e1 = (const Element*)a;
    const Element* e2 = (const Element*)b;
    const QueueItem* item1 = &e1->item;
    const QueueItem* item2 = &e2->item;

    retVal = (item1->firstLeft > item2->firstLeft);
    if (item1->cost != item2->cost) {
        retVal = (item1->cost > item2->cost);
    }

    return retVal;
}
static void swap(Element* arr, int i, int j) {
    Element t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}
typedef struct PriorityQueue {
    Element* arr;
    int capacity;
    int queueSize;
    CompareFunc lessFunc;
} PriorityQueue;
PriorityQueue* createPriorityQueue(CompareFunc cmpFunc) {
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
static void down(Element* arr, int size, int i, CompareFunc cmpFunc) {
    int left, right, smallest;
    while (true) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        smallest = i;
        if (left < size && cmpFunc(&arr[smallest], &arr[left])) {
            smallest = left;
        }
        if (right < size && cmpFunc(&arr[smallest], &arr[right])) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        swap(arr, i, smallest);
        i = smallest;
    }
}
void enQueue(PriorityQueue* obj, const QueueItem* item) {
    if (obj->queueSize == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = (Element*)realloc(obj->arr, sizeof(Element) * obj->capacity);
    }

    obj->arr[obj->queueSize].item = *item;

    int parent;
    int i = obj->queueSize;
    while (i > 0) {
        parent = (i - 1) / 2;
        if (!obj->lessFunc(&obj->arr[parent], &obj->arr[i])) {
            break;
        }
        swap(obj->arr, i, parent);
        i = parent;
    }

    obj->queueSize++;
}
QueueItem* deQueue(PriorityQueue* obj) {
    QueueItem* pRetVal = NULL;

    if (obj->queueSize == 0) {
        return pRetVal;
    }

    swap(obj->arr, 0, obj->queueSize - 1);
    pRetVal = &obj->arr[obj->queueSize - 1].item;
    obj->queueSize--;
    if (obj->queueSize > 0) {
        down(obj->arr, obj->queueSize, 0, obj->lessFunc);
    }

    return pRetVal;
}
QueueItem* front(const PriorityQueue* obj) {
    QueueItem* pRetVal = NULL;

    if (obj->queueSize != 0) {
        pRetVal = &obj->arr[0].item;
    }

    return pRetVal;
}
bool isEmpty(const PriorityQueue* obj) {
    bool retVal = (obj->queueSize == 0);

    return retVal;
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

#endif  // HEAP_H
int minimumPairRemoval(int* nums, int numsSize) {
    int retVal = 0;

    Node** nodes = (Node**)malloc(numsSize * sizeof(Node*));
    if (nodes == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < numsSize; i++) {
        nodes[i] = createNode(nums[i], i);
        if (nodes[i] == NULL) {
            perror("malloc");
            goto exit_nodes;
        }
        if (i > 0) {
            nodes[i - 1]->next = nodes[i];
            nodes[i]->prev = nodes[i - 1];
        }
    }

    PriorityQueue* pq = createPriorityQueue(itemLess);
    if (pq == NULL) {
        perror("malloc");
        goto exit_nodes;
    }
    int decreaseCount = 0;
    for (int i = 1; i < numsSize; i++) {
        QueueItem item;
        item.first = nodes[i - 1];
        item.second = nodes[i];
        item.cost = item.first->value + item.second->value;
        item.firstLeft = item.first->left;
        item.secondLeft = item.second->left;
        enQueue(pq, &item);
        if (nums[i - 1] > nums[i]) {
            decreaseCount++;
        }
    }

    bool* merged = (bool*)calloc(numsSize, sizeof(bool));
    if (merged == NULL) {
        perror("calloc");
        goto exit_pq;
    }
    while (decreaseCount > 0 && !isEmpty(pq)) {
        QueueItem* itemPtr = deQueue(pq);
        if (itemPtr == NULL) {
            break;
        }

        QueueItem item = *itemPtr;
        if ((merged[item.firstLeft] == true) || (merged[item.secondLeft] == true)) {
            continue;
        }

        Node* first = item.first;
        Node* second = item.second;
        long long cost = item.cost;
        if ((first == NULL) || (second == NULL)) {
            continue;
        }
        if (first->next != second) {
            continue;
        }
        if (first->value + second->value != cost) {
            continue;
        }

        retVal++;

        if (first->value > second->value) {
            decreaseCount--;
        }

        Node* prevNode = first->prev;
        Node* nextNode = second->next;
        first->next = nextNode;
        if (nextNode != NULL) {
            nextNode->prev = first;
        }
        second->prev = NULL;
        second->next = NULL;

        if (prevNode != NULL) {
            if (prevNode->value > first->value && prevNode->value <= cost) {
                decreaseCount--;
            }
            if (prevNode->value <= first->value && prevNode->value > cost) {
                decreaseCount++;
            }

            QueueItem newItem;
            newItem.first = prevNode;
            newItem.second = first;
            newItem.cost = prevNode->value + cost;
            newItem.firstLeft = prevNode->left;
            newItem.secondLeft = first->left;
            enQueue(pq, &newItem);
        }

        if (nextNode != NULL) {
            if (second->value > nextNode->value && cost <= nextNode->value) {
                decreaseCount--;
            }
            if (second->value <= nextNode->value && cost > nextNode->value) {
                decreaseCount++;
            }

            QueueItem newItem;
            newItem.first = first;
            newItem.second = nextNode;
            newItem.cost = cost + nextNode->value;
            newItem.firstLeft = first->left;
            newItem.secondLeft = nextNode->left;
            enQueue(pq, &newItem);
        }

        first->value = cost;
        merged[second->left] = true;
    }

    //
    free(merged);
    merged = NULL;
exit_pq:
    freeQueue(pq);
    pq = NULL;
exit_nodes:
    for (int i = 0; i < numsSize; i++) {
        if (nodes[i]) {
            free(nodes[i]);
            nodes[i] = NULL;
        }
    }
    free(nodes);
    nodes = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{5, 2, 3, 1}, 4}, {{1, 2, 2}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [5,2,3,1]
     *  Output: 2
     *
     *  Input: nums = [1,2,2]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minimumPairRemoval(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
