#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    int priority;
    int taskId;
} Element;
typedef bool (*compare)(const void *, const void *);
typedef struct PriorityQueue {
    Element *arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;
static bool less(const void *a, const void *b) {
    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    if (e1->priority == e2->priority) {
        return e1->taskId < e2->taskId;
    }
    return e1->priority < e2->priority;
}
static void memswap(void *m1, void *m2, size_t size) {
    unsigned char *a = (unsigned char *)m1;
    unsigned char *b = (unsigned char *)m2;
    while (size--) {
        *b ^= *a;
        *a ^= *b;
        *b ^= *a;

        a++;
        b++;
    }
}
static void swap(Element *arr, int i, int j) { memswap(&arr[i], &arr[j], sizeof(Element)); }
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
bool isEmpty(const PriorityQueue *obj) { return obj->queueSize == 0; }
Element *front(const PriorityQueue *obj) {
    if (obj->queueSize == 0) {
        return NULL;
    } else {
        return &obj->arr[0];
    }
}
void clear(PriorityQueue *obj) { obj->queueSize = 0; }
int size(const PriorityQueue *obj) { return obj->queueSize; }
void freeQueue(PriorityQueue *obj) {
    free(obj->arr);
    free(obj);
}

#endif  // PRIORITY_QUEUE_H
#ifndef HASH_H
#define HASH_H

typedef struct Pair {
    int priority;
    int userId;
} Pair;
typedef struct {
    int key;
    Pair val;
    UT_hash_handle hh;
} HashItem;
HashItem *hashFindItem(HashItem **obj, int key) {
    HashItem *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    return pEntry;
}
bool hashAddItem(HashItem **obj, int key, Pair val) {
    if (hashFindItem(obj, key)) {
        return false;
    }
    HashItem *pEntry = (HashItem *)malloc(sizeof(HashItem));
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_INT(*obj, key, pEntry);
    return true;
}
bool hashSetItem(HashItem **obj, int key, Pair val) {
    HashItem *pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        hashAddItem(obj, key, val);
    } else {
        pEntry->val = val;
    }
    return true;
}
Pair *hashGetItem(HashItem **obj, int key) {
    HashItem *pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        return NULL;
    }
    return &pEntry->val;
}
void hashEraseItem(HashItem **obj, int key) {
    HashItem *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    if (pEntry != NULL) {
        HASH_DEL(*obj, pEntry);
        free(pEntry);
    }
}
void hashFree(HashItem **obj) {
    HashItem *curr = NULL, *tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}

#endif  // HASH_H
typedef struct {
    HashItem *taskInfo;
    PriorityQueue *heap;
} TaskManager;
TaskManager *taskManagerCreate(int **tasks, int tasksSize, int *tasksColSize) {
    TaskManager *obj = NULL;

    obj = (TaskManager *)malloc(sizeof(TaskManager));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->taskInfo = NULL;
    obj->heap = createPriorityQueue(less);

    for (int i = 0; i < tasksSize; i++) {
        int userId = tasks[i][0];
        int taskId = tasks[i][1];
        int priority = tasks[i][2];

        Pair val = {priority, userId};
        hashAddItem(&obj->taskInfo, taskId, val);

        Element e = {priority, taskId};
        enQueue(obj->heap, &e);
    }

    return obj;
}
void taskManagerAdd(TaskManager *obj, int userId, int taskId, int priority) {
    Pair val = {priority, userId};
    hashAddItem(&obj->taskInfo, taskId, val);
    Element e = {priority, taskId};
    enQueue(obj->heap, &e);
}
void taskManagerEdit(TaskManager *obj, int taskId, int newPriority) {
    if (hashFindItem(&obj->taskInfo, taskId)) {
        Pair *p = hashGetItem(&obj->taskInfo, taskId);
        Pair val = {newPriority, p->userId};
        hashSetItem(&obj->taskInfo, taskId, val);
        Element e = {newPriority, taskId};
        enQueue(obj->heap, &e);
    }
}
void taskManagerRmv(TaskManager *obj, int taskId) {
    //
    hashEraseItem(&obj->taskInfo, taskId);
}
int taskManagerExecTop(TaskManager *obj) {
    int retVal = -1;

    while (!isEmpty(obj->heap)) {
        Element *p = front(obj->heap);
        int priority = p->priority;
        int taskId = p->taskId;
        deQueue(obj->heap);
        if (hashFindItem(&obj->taskInfo, taskId) && hashGetItem(&obj->taskInfo, taskId)->priority == priority) {
            int userId = hashGetItem(&obj->taskInfo, taskId)->userId;
            hashEraseItem(&obj->taskInfo, taskId);
            retVal = userId;
            break;
        }
    }

    return retVal;
}
void taskManagerFree(TaskManager *obj) {
    freeQueue(obj->heap);
    hashFree(&obj->taskInfo);
    free(obj);
}
/**
 * Your TaskManager struct will be instantiated and called as such:
 * TaskManager* obj = taskManagerCreate(tasks, tasksSize, tasksColSize);
 * taskManagerAdd(obj, userId, taskId, priority);
 * taskManagerEdit(obj, taskId, newPriority);
 * taskManagerRmv(obj, taskId);
 * int param_4 = taskManagerExecTop(obj);
 * taskManagerFree(obj);
 */

int main(int argc, char **argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char *methods;
        int tasks[MAX_SIZE][MAX_SIZE];
        int tasksSize;
        int tasksColSize[MAX_SIZE];
        int userId;
        int taskId;
        int priority;
        int newPriority;
    } testCase[] = {{"TaskManager",
                     {
                         {1, 101, 10},
                         {2, 102, 20},
                         {3, 103, 15},
                     },
                     3,
                     {3, 3, 3},
                     0,
                     0,
                     0,
                     0},
                    {"add", {}, 0, {}, 4, 104, 5, 0},
                    {"edit", {}, 0, {}, 0, 102, 0, 8},
                    {"execTop", {}, 0, {}, 0, 0, 0, 0},
                    {"rmv", {}, 0, {}, 0, 101, 0, 0},
                    {"add", {}, 0, {}, 5, 105, 15, 0},
                    {"execTop", {}, 0, {}, 0, 0, 0, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input:
     *  ["TaskManager", "add", "edit", "execTop", "rmv", "add", "execTop"]
     *  [[[[1, 101, 10], [2, 102, 20], [3, 103, 15]]], [4, 104, 5], [102, 8], [], [101], [5, 105, 15], []]
     *  Output:
     *  [null, null, null, 3, null, null, 5]
     */

    printf("Input\n");
    printf("[");
    for (int i = 0; i < numberOfTestCase; ++i) {
        printf("%s\"%s\"", (i == 0) ? "" : ", ", testCase[i].methods);
    }
    printf("]\n");
    printf("[");
    for (int i = 0; i < numberOfTestCase; ++i) {
        printf("%s[", (i == 0) ? "" : ", ");

        bool flag = false;
        for (int j = 0; j < testCase[i].tasksSize; ++j) {
            printf("%s[", (j == 0) ? "" : ", ");
            for (int k = 0; k < testCase[i].tasksColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ", ", testCase[i].tasks[j][k]);
            }
            printf("]");
            flag = true;
        }
        if (testCase[i].userId != 0) {
            printf("%s%d", (flag == true) ? ", " : "", testCase[i].userId);
            flag = true;
        }
        if (testCase[i].taskId != 0) {
            printf("%s%d", (flag == true) ? ", " : "", testCase[i].taskId);
            flag = true;
        }
        if (testCase[i].priority != 0) {
            printf("%s%d", (flag == true) ? ", " : "", testCase[i].priority);
            flag = true;
        }
        if (testCase[i].newPriority != 0) {
            printf("%s%d", (flag == true) ? ", " : "", testCase[i].newPriority);
            flag = true;
        }

        printf("]");
    }
    printf("]\n");

    TaskManager *obj = NULL;
    int **pTasks = NULL;

    printf("Output\n");
    printf("[");
    for (int i = 0; i < numberOfTestCase; ++i) {
        if (strcmp(testCase[i].methods, "TaskManager") == 0) {
            pTasks = (int **)malloc(sizeof(int *) * testCase[i].tasksSize);
            for (int j = 0; j < testCase[i].tasksSize; ++j) {
                pTasks[j] = (int *)malloc(sizeof(int) * testCase[i].tasksColSize[j]);
                memcpy(pTasks[j], testCase[i].tasks[j], sizeof(int) * testCase[i].tasksColSize[j]);
            }

            obj = taskManagerCreate(pTasks, testCase[i].tasksSize, testCase[i].tasksColSize);
            printf("%snull", (i == 0) ? "" : ", ");
        } else if (strcmp(testCase[i].methods, "add") == 0) {
            taskManagerAdd(obj, testCase[i].userId, testCase[i].taskId, testCase[i].priority);
            printf("%snull", (i == 0) ? "" : ", ");
        } else if (strcmp(testCase[i].methods, "edit") == 0) {
            taskManagerEdit(obj, testCase[i].taskId, testCase[i].newPriority);
            printf("%snull", (i == 0) ? "" : ", ");
        } else if (strcmp(testCase[i].methods, "rmv") == 0) {
            taskManagerRmv(obj, testCase[i].taskId);
            printf("%snull", (i == 0) ? "" : ", ");
        } else if (strcmp(testCase[i].methods, "execTop") == 0) {
            int retInt = taskManagerExecTop(obj);
            printf("%s%d", (i == 0) ? "" : ", ", retInt);
        }
    }
    printf("]\n");

    for (int i = 0; i < numberOfTestCase; ++i) {
        if (strcmp(testCase[i].methods, "TaskManager") == 0) {
            for (int j = 0; j < testCase[i].tasksSize; ++j) {
                free(pTasks[j]);
                pTasks[j] = NULL;
            }
            free(pTasks);
            pTasks = NULL;
        }
    }
    taskManagerFree(obj);
    obj = NULL;

    return EXIT_SUCCESS;
}
