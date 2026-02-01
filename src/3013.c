#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef HEAP_H
#define HEAP_H

#define MIN_QUEUE_SIZE (64)
typedef struct Element {
    int data[2];
} Element;
typedef bool (*compare)(const void*, const void*);
typedef struct PriorityQueue {
    Element* arr;
    int capacity;
    int queueSize;
    compare cmpFunc;
} PriorityQueue;
static bool minHeapCmp(const void* a, const void* b) {
    bool retVal = false;

    Element* e1 = (Element*)a;
    Element* e2 = (Element*)b;
    retVal = (e1->data[0] > e2->data[0]);

    return retVal;
}
static bool maxHeapCmp(const void* a, const void* b) {
    bool retVal = false;

    Element* e1 = (Element*)a;
    Element* e2 = (Element*)b;
    retVal = (e1->data[0] < e2->data[0]);

    return retVal;
}
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
    pObj->cmpFunc = cmpFunc;

    return pObj;
}
void heapify(PriorityQueue* obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->cmpFunc);
    }
}
void enQueue(PriorityQueue* obj, Element* e) {
    if (obj->queueSize == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = realloc(obj->arr, sizeof(Element) * obj->capacity);
    }
    memcpy(&obj->arr[obj->queueSize], e, sizeof(Element));
    for (int i = obj->queueSize; i > 0 && obj->cmpFunc(&obj->arr[(i - 1) / 2], &obj->arr[i]); i = (i - 1) / 2) {
        swap(obj->arr, i, (i - 1) / 2);
    }
    obj->queueSize++;
}
Element* deQueue(PriorityQueue* obj) {
    Element* pRetVal = NULL;

    if (obj->queueSize == 0) {
        return pRetVal;
    }

    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->cmpFunc);
    pRetVal = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;

    return pRetVal;
}
bool isEmpty(const PriorityQueue* obj) {
    bool retVal = (obj->queueSize == 0);

    return retVal;
}
Element* top(const PriorityQueue* obj) {
    Element* pRetVal = NULL;

    if (obj->queueSize != 0) {
        pRetVal = &obj->arr[0];
    }

    return pRetVal;
}
int size(const PriorityQueue* obj) {
    int retVal = obj->queueSize;

    return retVal;
}
void clear(PriorityQueue* obj) {
    //
    obj->queueSize = 0;
}
void freeQueue(PriorityQueue* obj) {
    free(obj->arr);
    free(obj);
}

#endif  // HEAP_H
#ifndef HASH_H
#define HASH_H

typedef struct HashItem {
    int key;
    int val;
    UT_hash_handle hh;
} HashItem;
HashItem* hashFindItem(HashItem** obj, int key) {
    HashItem* pEntry = NULL;

    HASH_FIND_INT(*obj, &key, pEntry);

    return pEntry;
}
bool hashAddItem(HashItem** obj, int key, int val) {
    bool retVal = false;

    if (hashFindItem(obj, key)) {
        return retVal;
    }
    HashItem* pEntry = (HashItem*)malloc(sizeof(HashItem));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
void hashSetItem(HashItem** obj, int key, int val) {
    HashItem* pEntry = hashFindItem(obj, key);
    if (pEntry == NULL) {
        hashAddItem(obj, key, val);
    } else {
        pEntry->val = val;
    }
}
int hashGetItem(HashItem** obj, int key, int defaultVal) {
    int retVal = defaultVal;

    HashItem* pEntry = hashFindItem(obj, key);
    if (pEntry != NULL) {
        retVal = pEntry->val;
    }

    return retVal;
}
void hashEraseItem(HashItem** obj, int key) {
    HashItem* pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    if (pEntry != NULL) {
        HASH_DEL(*obj, pEntry);
        free(pEntry);
    }
}
void hashFree(HashItem** obj) {
    HashItem* curr = NULL;
    HashItem* tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}

#endif  // HASH_H
typedef struct {
    int k;
    HashItem* st1;
    HashItem* st2;
    PriorityQueue* tree1;
    PriorityQueue* tree2;
    int st1Size;
    int st2Size;
    long long sm;
} Container;
Container* createContainer(int k) {
    Container* pObj = NULL;

    pObj = (Container*)malloc(sizeof(Container));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->k = k;
    pObj->st1 = NULL;
    pObj->st2 = NULL;
    pObj->tree1 = createPriorityQueue(maxHeapCmp);
    pObj->tree2 = createPriorityQueue(minHeapCmp);
    pObj->st1Size = 0;
    pObj->st2Size = 0;
    pObj->sm = 0;

    return pObj;
}
void addOne(HashItem** map, PriorityQueue* heap, int key) {
    int count = hashGetItem(map, key, 0);
    hashSetItem(map, key, count + 1);
    if (count == 0) {
        Element e;
        e.data[0] = key;
        e.data[1] = 0;
        enQueue(heap, &e);
    }
}
void removeOne(HashItem** map, PriorityQueue* heap, int key) {
    HashItem* entry = hashFindItem(map, key);
    if (entry == NULL) {
        return;
    }
    entry->val--;
    if (entry->val == 0) {
        hashEraseItem(map, key);
    }
}
void adjust(Container* cnt) {
    while (cnt->st1Size < cnt->k && cnt->st2Size > 0) {
        while (isEmpty(cnt->tree2) == false) {
            Element* topElem = top(cnt->tree2);
            if ((topElem == NULL) || (hashGetItem(&cnt->st2, topElem->data[0], 0) == 0)) {
                deQueue(cnt->tree2);
            } else {
                break;
            }
        }

        if (isEmpty(cnt->tree2) == true) {
            break;
        }

        int x = top(cnt->tree2)->data[0];
        removeOne(&cnt->st2, cnt->tree2, x);
        cnt->st2Size--;
        addOne(&cnt->st1, cnt->tree1, x);
        cnt->st1Size++;
        cnt->sm += x;
    }

    while (cnt->st1Size > cnt->k) {
        while (isEmpty(cnt->tree1) == false) {
            Element* topElem = top(cnt->tree1);
            if ((topElem == NULL) || (hashGetItem(&cnt->st1, topElem->data[0], 0) == 0)) {
                deQueue(cnt->tree1);
            } else {
                break;
            }
        }

        if (isEmpty(cnt->tree1) == true) {
            break;
        }
        int x = top(cnt->tree1)->data[0];
        removeOne(&cnt->st1, cnt->tree1, x);
        cnt->st1Size--;
        cnt->sm -= x;

        addOne(&cnt->st2, cnt->tree2, x);
        cnt->st2Size++;
    }
}
void containerAdd(Container* cnt, int x) {
    while (isEmpty(cnt->tree2) == false) {
        Element* topElem = top(cnt->tree2);
        if ((topElem == NULL) || (hashGetItem(&cnt->st2, topElem->data[0], 0) == 0)) {
            deQueue(cnt->tree2);
        } else {
            break;
        }
    }

    if (cnt->st2Size > 0 && !isEmpty(cnt->tree2) && x >= top(cnt->tree2)->data[0]) {
        addOne(&cnt->st2, cnt->tree2, x);
        cnt->st2Size++;
    } else {
        addOne(&cnt->st1, cnt->tree1, x);
        cnt->st1Size++;
        cnt->sm += x;
    }

    adjust(cnt);
}
void containerErase(Container* cnt, int x) {
    if (hashGetItem(&cnt->st1, x, 0) > 0) {
        removeOne(&cnt->st1, cnt->tree1, x);
        cnt->st1Size--;
        cnt->sm -= x;
    } else if (hashGetItem(&cnt->st2, x, 0) > 0) {
        removeOne(&cnt->st2, cnt->tree2, x);
        cnt->st2Size--;
    }

    adjust(cnt);
}
long long containerSum(Container* cnt) {
    long long retVal = cnt->sm;

    return retVal;
}
void freeContainer(Container* cnt) {
    hashFree(&cnt->st1);
    hashFree(&cnt->st2);
    freeQueue(cnt->tree1);
    freeQueue(cnt->tree2);
    free(cnt);
}
long long minimumCost(int* nums, int numsSize, int k, int dist) {
    long long retVal = 0;

    Container* cnt = createContainer(k - 2);
    for (int i = 1; i < k - 1; i++) {
        containerAdd(cnt, nums[i]);
    }

    retVal = containerSum(cnt) + nums[k - 1];
    for (int i = k; i < numsSize; i++) {
        int j = i - dist - 1;
        if (j > 0) {
            containerErase(cnt, nums[j]);
        }
        containerAdd(cnt, nums[i - 1]);

        long long current = containerSum(cnt) + nums[i];
        if (current < retVal) {
            retVal = current;
        }
    }
    retVal += nums[0];

    //
    freeContainer(cnt);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
        int dist;
    } testCase[] = {{{1, 3, 2, 6, 4, 2}, 6, 3, 3}, {{10, 1, 2, 2, 2, 1}, 6, 4, 3}, {{10, 8, 18, 9}, 4, 3, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,2,6,4,2], k = 3, dist = 3
     *  Output: 5
     *
     *  Input: nums = [10,1,2,2,2,1], k = 4, dist = 3
     *  Output: 15
     *
     *  Input: nums = [10,8,18,9], k = 3, dist = 1
     *  Output: 36
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d, dist = %d\n", testCase[i].k, testCase[i].dist);

        answer = minimumCost(testCase[i].nums, testCase[i].numsSize, testCase[i].k, testCase[i].dist);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
