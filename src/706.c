#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LIST_H
#define LIST_H

struct List {
    int key;
    int val;
    struct List* next;
};
void listPush(struct List* pHead, int key, int value) {
    struct List* pNew = (struct List*)malloc(sizeof(struct List));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->key = key;
    pNew->val = value;
    pNew->next = pHead->next;
    pHead->next = pNew;
}
void listDelete(struct List* pHead, int key) {
    struct List* pFree = NULL;
    struct List* iterator;
    for (iterator = pHead; iterator->next; iterator = iterator->next) {
        if (iterator->next->key == key) {
            pFree = iterator->next;
            iterator->next = pFree->next;
            free(pFree);
            pFree = NULL;
            break;
        }
    }
}
struct List* listFind(struct List* pHead, int key) {
    struct List* pRetVal = NULL;

    struct List* iterator;
    for (iterator = pHead; iterator->next; iterator = iterator->next) {
        if (iterator->next->key == key) {
            pRetVal = iterator->next;
            break;
        }
    }

    return pRetVal;
}
void listFree(struct List* pHead) {
    struct List* pFree = NULL;
    while (pHead->next) {
        pFree = pHead->next;
        pHead->next = pFree->next;
        free(pFree);
        pFree = NULL;
    }
}

#endif
#define MyHashMapMod (1000)
typedef struct {
    struct List* map;
} MyHashMap;
MyHashMap* myHashMapCreate() {
    MyHashMap* pRetVal = NULL;

    pRetVal = (MyHashMap*)malloc(sizeof(MyHashMap));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    pRetVal->map = (struct List*)malloc(sizeof(struct List) * MyHashMapMod);
    if (pRetVal->map == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    int i;
    for (i = 0; i < MyHashMapMod; i++) {
        pRetVal->map[i].key = i;
        pRetVal->map[i].val = -1;
        pRetVal->map[i].next = NULL;
    }

    return pRetVal;
}
void myHashMapPut(MyHashMap* obj, int key, int value) {
    int idx = key % MyHashMapMod;
    struct List* pRetVal = listFind(&(obj->map[idx]), key);
    if (pRetVal == NULL) {
        listPush(&(obj->map[idx]), key, value);
    } else {
        pRetVal->val = value;
    }
}
int myHashMapGet(MyHashMap* obj, int key) {
    int retVal = -1;

    int idx = key % MyHashMapMod;
    struct List* pRetVal = listFind(&(obj->map[idx]), key);
    if (pRetVal != NULL) {
        retVal = pRetVal->val;
    }

    return retVal;
}
void myHashMapRemove(MyHashMap* obj, int key) {
    int idx = key % MyHashMapMod;
    listDelete(&(obj->map[idx]), key);
}
void myHashMapFree(MyHashMap* obj) {
    int i;
    for (i = 0; i < MyHashMapMod; i++) {
        listFree(&(obj->map[i]));
    }
    free(obj->map);
    obj->map = NULL;

    free(obj);
    obj = NULL;
}
/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);
 * int param_2 = myHashMapGet(obj, key);
 * myHashMapRemove(obj, key);
 * myHashMapFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][4];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"},
                     {{}, {1, 1}, {2, 2}, {1}, {3}, {2, 1}, {2}, {2}, {2}},
                     {0, 2, 2, 1, 1, 2, 1, 1, 1},
                     9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
     *  [[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
     *  Output
     *  [null, null, null, 1, -1, null, 1, null, -1]
     */

    MyHashMap* obj = NULL;
    int retInt;
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
            for (k = 0; k < testCase[i].valSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ", ", testCase[i].val[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "MyHashMap") == 0) {
                obj = myHashMapCreate();
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "put") == 0) {
                myHashMapPut(obj, testCase[i].val[j][0], testCase[i].val[j][1]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "get") == 0) {
                retInt = myHashMapGet(obj, testCase[i].val[j][0]);
                printf("%s%d", (j == 0) ? "" : ", ", retInt);
            } else if (strcmp(testCase[i].methods[j], "remove") == 0) {
                myHashMapRemove(obj, testCase[i].val[j][0]);
                printf("%snull", (j == 0) ? "" : ", ");
            }
        }
        printf("]\n");

        myHashMapFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
