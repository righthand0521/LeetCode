#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/lfu-cache/solutions/1810523/by-heng-deng-shi-2ojp/
#if 1
typedef struct ValueListNode_s {
    int key;
    int value;
    int counter;
    struct ValueListNode_s *prev;
    struct ValueListNode_s *next;
} ValueListNode;
typedef struct CounterListNode_s {
    ValueListNode *head;
    struct CounterListNode_s *prev;
    struct CounterListNode_s *next;
} CounterListNode;
#endif
typedef struct {
    int capacity;
    int currentCounter;
    ValueListNode **keyHash;
    CounterListNode **counterHash;
    CounterListNode *head;
} LFUCache;
#if 1
void removeValueNode(CounterListNode *counterNode, ValueListNode *valueNode) {
    if (valueNode->next == valueNode) {
        counterNode->head = NULL;
        return;
    }

    valueNode->prev->next = valueNode->next;
    valueNode->next->prev = valueNode->prev;
    if (counterNode->head == valueNode) {
        counterNode->head = valueNode->next;
    }
}
void insertValueNode(CounterListNode *counterNode, ValueListNode *valueNode) {
    ValueListNode *tail = NULL;

    if (NULL == counterNode->head) {
        valueNode->prev = valueNode;
        valueNode->next = valueNode;
    } else {
        tail = counterNode->head->prev;
        valueNode->prev = tail;
        valueNode->next = counterNode->head;
        counterNode->head->prev = valueNode;
        tail->next = valueNode;
    }

    counterNode->head = valueNode;
}
void removeCounterNode(LFUCache *obj, CounterListNode *counterNode) {
    if (obj->head == counterNode) {
        obj->head = counterNode->next;
        if (NULL != obj->head) {
            obj->head->prev = NULL;
        }

        return;
    }

    counterNode->prev->next = counterNode->next;
    if (NULL != counterNode->next) {
        counterNode->next->prev = counterNode->prev;
    }
}
void insertCounterNode(LFUCache *obj, CounterListNode *counterPrev, CounterListNode *counterNode) {
    if (NULL == counterPrev) {
        counterNode->prev = NULL;
        counterNode->next = obj->head;
        if (NULL != obj->head) {
            obj->head->prev = counterNode;
        }
        obj->head = counterNode;

        return;
    }

    counterNode->prev = counterPrev;
    counterNode->next = counterPrev->next;
    if (NULL != counterPrev->next) {
        counterPrev->next->prev = counterNode;
    }
    counterPrev->next = counterNode;
}
#endif
LFUCache *lFUCacheCreate(int capacity) {
    LFUCache *pRetVal = NULL;

    pRetVal = (LFUCache *)malloc(sizeof(LFUCache));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    pRetVal->capacity = capacity;

    pRetVal->currentCounter = 0;

    // 0 <= key <= 10^5
    pRetVal->keyHash = (ValueListNode **)calloc(100001, sizeof(ValueListNode *));
    if (pRetVal->keyHash == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    // At most 2 * 10 ^ 5 calls will be made to get and put.
    pRetVal->counterHash = (CounterListNode **)calloc(200001, sizeof(CounterListNode *));
    if (pRetVal->counterHash == NULL) {
        perror("malloc");
        free(pRetVal->keyHash);
        pRetVal->keyHash = NULL;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    pRetVal->head = NULL;

    return pRetVal;
}
int lFUCacheGet(LFUCache *obj, int key) {
    int retVal = -1;

    CounterListNode *counterNode = NULL;
    CounterListNode *counterNew = NULL;
    ValueListNode *valueNode = obj->keyHash[key];
    if (NULL != valueNode) {
        retVal = valueNode->value;

        counterNode = obj->counterHash[valueNode->counter];

        valueNode->counter++;
        counterNew = obj->counterHash[valueNode->counter];

        removeValueNode(counterNode, valueNode);

        if (NULL == counterNew) {
            counterNew = (CounterListNode *)calloc(1, sizeof(CounterListNode));
            if (counterNew == NULL) {
                perror("malloc");
                retVal = -1;
                return retVal;
            }
            obj->counterHash[valueNode->counter] = counterNew;
            insertCounterNode(obj, counterNode, counterNew);
        }

        if (NULL == counterNode->head) {
            removeCounterNode(obj, counterNode);
            free(counterNode);
            obj->counterHash[valueNode->counter - 1] = NULL;
        }

        insertValueNode(counterNew, valueNode);
    }

    return retVal;
}
void lFUCachePut(LFUCache *obj, int key, int value) {
    if (0 == obj->capacity) {
        return;
    }

    CounterListNode *counterNode = NULL;
    CounterListNode *counterNew = NULL;
    ValueListNode *valueNode = obj->keyHash[key];
    if (NULL != valueNode) {
        valueNode->value = value;

        counterNode = obj->counterHash[valueNode->counter];

        valueNode->counter++;
        counterNew = obj->counterHash[valueNode->counter];

        removeValueNode(counterNode, valueNode);

        if (NULL == counterNew) {
            counterNew = (CounterListNode *)calloc(1, sizeof(CounterListNode));
            if (counterNew == NULL) {
                perror("malloc");
                return;
            }
            obj->counterHash[valueNode->counter] = counterNew;
            insertCounterNode(obj, counterNode, counterNew);
        }

        if (NULL == counterNode->head) {
            removeCounterNode(obj, counterNode);
            free(counterNode);
            obj->counterHash[valueNode->counter - 1] = NULL;
        }

        insertValueNode(counterNew, valueNode);

        return;
    }

    int keyRemove = 0;
    ValueListNode *valueRemove = NULL;
    if (obj->capacity > obj->currentCounter) {
        obj->currentCounter++;
    } else {
        counterNode = obj->head;

        valueRemove = counterNode->head->prev;
        keyRemove = valueRemove->key;

        removeValueNode(counterNode, valueRemove);

        if (NULL == counterNode->head) {
            removeCounterNode(obj, counterNode);
            free(counterNode);
            obj->counterHash[valueRemove->counter] = NULL;
        }
        free(valueRemove);
        obj->keyHash[keyRemove] = NULL;
    }

    valueNode = (ValueListNode *)calloc(1, sizeof(ValueListNode));
    if (valueNode == NULL) {
        perror("malloc");
        return;
    }
    valueNode->key = key;
    valueNode->value = value;
    valueNode->counter = 1;
    obj->keyHash[key] = valueNode;

    counterNew = obj->counterHash[1];

    if (NULL == counterNew) {
        counterNew = (CounterListNode *)calloc(1, sizeof(CounterListNode));
        if (counterNew == NULL) {
            perror("malloc");
            return;
        }
        obj->counterHash[1] = counterNew;

        insertCounterNode(obj, NULL, counterNew);
    }

    insertValueNode(counterNew, valueNode);
}
void lFUCacheFree(LFUCache *obj) {
    ValueListNode *valueNode = NULL;
    ValueListNode *valueNext = NULL;
    CounterListNode *counterNext = NULL;
    CounterListNode *counterNode = obj->head;
    while (NULL != counterNode) {
        counterNext = counterNode->next;

        valueNode = counterNode->head;
        do {
            valueNext = valueNode->next;
            free(valueNode);
            valueNode = valueNext;
        } while (counterNode->head != valueNode);
        free(counterNode);

        counterNode = counterNext;
    }

    free(obj->keyHash);
    free(obj->counterHash);
    free(obj);
}
/**
 * Your LFUCache struct will be instantiated and called as such:
 * LFUCache* obj = lFUCacheCreate(capacity);
 * int param_1 = lFUCacheGet(obj, key);
 * lFUCachePut(obj, key, value);
 * lFUCacheFree(obj);
 */

int main(int argc, char **argv) {
#define MAX_SIZE (20000)
#define DISPLAY_NULL (-1)
    struct testCaseType {
        char *methods[MAX_SIZE];
        int value[MAX_SIZE][2];
        int valueSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"},
                     {{2}, {1, 1}, {2, 2}, {1}, {3, 3}, {2}, {3}, {4, 4}, {1}, {3}, {4}},
                     {1, 2, 2, 1, 2, 1, 1, 2, 1, 1, 1},
                     11}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    LFUCache *obj = NULL;
    int retInt = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[", (j == 0) ? "" : ", ");
            for (k = 0; k < testCase[i].valueSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ", ", testCase[i].value[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "LFUCache") == 0) {
                obj = lFUCacheCreate(testCase[i].value[j][0]);
                if (obj == NULL) {
                    return EXIT_FAILURE;
                }
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "get") == 0) {
                retInt = lFUCacheGet(obj, testCase[i].value[j][0]);
                printf("%s%d", (j == 0) ? "" : ", ", retInt);
            } else if (strcmp(testCase[i].methods[j], "put") == 0) {
                lFUCachePut(obj, testCase[i].value[j][0], testCase[i].value[j][1]);
                printf("%snull", (j == 0) ? "" : ", ");
            }
        }
        printf("]\n");

        lFUCacheFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
