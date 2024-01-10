#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LIST_H
#define LIST_H

struct List {
    int val;
    struct List* next;
};
void listPush(struct List* pHead, int value) {
    struct List* pNew = (struct List*)malloc(sizeof(struct List));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->val = value;
    pNew->next = pHead->next;
    pHead->next = pNew;
}
void listDelete(struct List* pHead, int value) {
    struct List* pFree = NULL;
    struct List* iterator;
    for (iterator = pHead; iterator->next; iterator = iterator->next) {
        if (iterator->next->val == value) {
            pFree = iterator->next;
            iterator->next = pFree->next;
            free(pFree);
            pFree = NULL;
            break;
        }
    }
}
bool listContains(struct List* pHead, int value) {
    bool retVal = false;

    struct List* iterator;
    for (iterator = pHead; iterator->next; iterator = iterator->next) {
        if (iterator->next->val == value) {
            retVal = true;
            break;
        }
    }

    return retVal;
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

#define MyHashMod (1000)
typedef struct {
    struct List* bucket;
} MyHashSet;
MyHashSet* myHashSetCreate() {
    MyHashSet* pRetVal = (MyHashSet*)malloc(sizeof(MyHashSet));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    pRetVal->bucket = (struct List*)malloc(sizeof(struct List) * MyHashMod);
    if (pRetVal->bucket == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    int i;
    for (i = 0; i < MyHashMod; i++) {
        pRetVal->bucket[i].val = 0;
        pRetVal->bucket[i].next = NULL;
    }

    return pRetVal;
}
void myHashSetAdd(MyHashSet* obj, int key) {
    int idx = key % MyHashMod;
    if (listContains(&(obj->bucket[idx]), key) == false) {
        listPush(&(obj->bucket[idx]), key);
    }
}
void myHashSetRemove(MyHashSet* obj, int key) {
    int idx = key % MyHashMod;
    listDelete(&(obj->bucket[idx]), key);
}
bool myHashSetContains(MyHashSet* obj, int key) {
    bool retVal = false;

    int idx = key % MyHashMod;
    retVal = listContains(&(obj->bucket[idx]), key);

    return retVal;
}
void myHashSetFree(MyHashSet* obj) {
    int i;
    for (i = 0; i < MyHashMod; i++) {
        listFree(&(obj->bucket[i]));
    }
    free(obj->bucket);
    obj->bucket = NULL;

    free(obj);
    obj = NULL;
}
/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);
 * myHashSetRemove(obj, key);
 * bool param_3 = myHashSetContains(obj, key);
 * myHashSetFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][1];
        int calls;
    } testCase[] = {{{"MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"},
                     {{}, {1}, {2}, {1}, {3}, {2}, {2}, {2}, {2}},
                     9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"]
     *  [[], [1], [2], [1], [3], [2], [2], [2], [2]]
     *  Output
     *  [null, null, null, true, false, null, true, null, false]
     */

    MyHashSet* obj = NULL;
    bool retBool;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[%d]", (j == 0) ? "" : ", ", testCase[i].val[j][0]);
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "MyHashSet") == 0) {
                obj = myHashSetCreate();
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "add") == 0) {
                myHashSetAdd(obj, testCase[i].val[j][0]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "remove") == 0) {
                myHashSetRemove(obj, testCase[i].val[j][0]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "contains") == 0) {
                retBool = myHashSetContains(obj, testCase[i].val[j][0]);
                printf("%s%s", (j == 0) ? "" : ", ", (retBool == true ? "true" : "false"));
            }
        }
        printf("]\n");

        myHashSetFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
