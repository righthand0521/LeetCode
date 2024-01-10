#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SINGLY_LINKED_LIST 1
#define DOUBLY_LINKED_LIST 1
#if (SINGLY_LINKED_LIST)
typedef struct MyLinkedList {
    int val;
    struct MyLinkedList* next;
} MyLinkedList;

MyLinkedList* myLinkedListCreate() {
    MyLinkedList* pNew = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->val = 0;
    pNew->next = NULL;

    return pNew;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
    int retVal = -1;

    if (index < 0) {
        return retVal;
    } else if ((obj->next == NULL) && (index > 0)) {
        return retVal;
    }

    MyLinkedList* pCurrent = obj->next;
    while (pCurrent != NULL) {
        if (index == 0) {
            break;
        }
        --index;
        pCurrent = pCurrent->next;
    }
    if ((pCurrent == NULL) && (index >= 0)) {
        return retVal;
    }
    retVal = pCurrent->val;

    return retVal;
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    MyLinkedList* pNew = NULL;
    pNew = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->val = val;
    pNew->next = NULL;

    pNew->next = obj->next;
    obj->next = pNew;
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    MyLinkedList* pNew = NULL;
    pNew = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->val = val;
    pNew->next = NULL;

    if (obj->next == NULL) {
        pNew->next = obj->next;
        obj->next = pNew;
        return;
    }
    MyLinkedList* pCurrent = obj;
    while (pCurrent->next != NULL) {
        pCurrent = pCurrent->next;
    }
    pCurrent->next = pNew;
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    if (index < 0) {
        return;
    } else if ((obj->next == NULL) && (index > 0)) {
        return;
    }

    MyLinkedList* pPrevious = NULL;
    MyLinkedList* pCurrent = obj->next;
    while (pCurrent != NULL) {
        if (index == 0) {
            break;
        }
        --index;
        pPrevious = pCurrent;
        pCurrent = pCurrent->next;
    }
    if (index > 0) {
        return;
    }

    MyLinkedList* pNew = NULL;
    pNew = (MyLinkedList*)malloc(sizeof(MyLinkedList));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->val = val;
    pNew->next = NULL;

    if (pPrevious == NULL) {
        pNew->next = obj->next;
        obj->next = pNew;
        return;
    }
    pPrevious->next = pNew;
    pNew->next = pCurrent;
}

void myLinkedListDeleteAtIndex(struct MyLinkedList* obj, int index) {
    if (index < 0) {
        return;
    } else if ((obj->next == NULL) && (index > 0)) {
        return;
    }

    MyLinkedList* pPrevious = NULL;
    MyLinkedList* pFree = obj->next;
    while (pFree != NULL) {
        if (index == 0) {
            break;
        }
        --index;
        pPrevious = pFree;
        pFree = pFree->next;
    }
    if ((pFree == NULL) && (index >= 0)) {
        return;
    }

    if (pPrevious == NULL) {
        obj->next = pFree->next;
    } else {
        pPrevious->next = pFree->next;
    }
    free(pFree);
    pFree = NULL;
}

void myLinkedListFree(MyLinkedList* obj) {
    MyLinkedList* pFree = NULL;
    MyLinkedList* pCurrent = obj;
    while (pCurrent != NULL) {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        free(pFree);
        pFree = NULL;
    }
}

void myLinkedListPrint(MyLinkedList* obj) {
    MyLinkedList* pCurrent = obj;
    while (pCurrent != NULL) {
        printf("%d -> ", pCurrent->val);
        pCurrent = pCurrent->next;
    }
    printf("NULL\n");
}
#elif (DOUBLY_LINKED_LIST)

#endif
/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);

 * myLinkedListAddAtHead(obj, val);

 * myLinkedListAddAtTail(obj, val);

 * myLinkedListAddAtIndex(obj, index, val);

 * myLinkedListDeleteAtIndex(obj, index);

 * myLinkedListFree(obj);
*/

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][2];
        int calls;
    } testCase[] = {
        {{"MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"},
         {{INT_MIN, INT_MIN}, {1, INT_MIN}, {3, INT_MIN}, {1, 2}, {1, INT_MIN}, {1, INT_MIN}, {1, INT_MIN}},
         7},
        {{"MyLinkedList", "addAtHead", "addAtHead", "addAtHead", "addAtIndex", "deleteAtIndex", "addAtHead",
          "addAtTail", "get", "addAtHead", "addAtIndex", "addAtHead"},
         {{INT_MIN, INT_MIN},
          {7, INT_MIN},
          {2, INT_MIN},
          {1, INT_MIN},
          {3, 0},
          {2, INT_MIN},
          {6, INT_MIN},
          {4, INT_MIN},
          {4, INT_MIN},
          {4, INT_MIN},
          {5, 0},
          {6, INT_MIN}},
         12},
        {{"MyLinkedList", "addAtHead", "deleteAtIndex"}, {{INT_MIN, INT_MIN}, {1, INT_MIN}, {0, INT_MIN}}, 3},
        {{"MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"},
         {{INT_MIN, INT_MIN}, {1, INT_MIN}, {3, INT_MIN}, {1, 2}, {1, INT_MIN}, {0, INT_MIN}, {0, INT_MIN}},
         7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    MyLinkedList* obj = NULL;
    int param_1;
    char val0[16];
    char val1[16];
    char displayStr[64];
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
            memset(val0, 0, sizeof(val0));
            if (testCase[i].val[j][0] != INT_MIN) {
                snprintf(val0, sizeof(val0), "%d", testCase[i].val[j][0]);
            }

            memset(val1, 0, sizeof(val1));
            if (testCase[i].val[j][1] != INT_MIN) {
                snprintf(val1, sizeof(val1), ",%d", testCase[i].val[j][1]);
            }

            memset(displayStr, 0, sizeof(displayStr));
            snprintf(displayStr, sizeof(displayStr), "%s%s", val0, val1);

            printf("%s[%s]", (j == 0) ? "" : ", ", displayStr);
        }
        printf("]\n");

        printf("Output\n");
        for (j = 0; j < testCase[i].calls; ++j) {
            param_1 = 0;

            if (strcmp(testCase[i].methods[j], "MyLinkedList") == 0) {
                obj = myLinkedListCreate();
            } else if (strcmp(testCase[i].methods[j], "get") == 0) {
                param_1 = myLinkedListGet(obj, testCase[i].val[j][0]);
            } else if (strcmp(testCase[i].methods[j], "addAtHead") == 0) {
                myLinkedListAddAtHead(obj, testCase[i].val[j][0]);
            } else if (strcmp(testCase[i].methods[j], "addAtTail") == 0) {
                myLinkedListAddAtTail(obj, testCase[i].val[j][0]);
            } else if (strcmp(testCase[i].methods[j], "addAtIndex") == 0) {
                myLinkedListAddAtIndex(obj, testCase[i].val[j][0], testCase[i].val[j][1]);
            } else if (strcmp(testCase[i].methods[j], "deleteAtIndex") == 0) {
                myLinkedListDeleteAtIndex(obj, testCase[i].val[j][0]);
            }

            if (strcmp(testCase[i].methods[j], "get") == 0) {
                printf("%16s: ", testCase[i].methods[j]);
                printf("%d\n", param_1);
            } else {
                printf("%16s: ", testCase[i].methods[j]);
                myLinkedListPrint(obj);
            }
        }
        myLinkedListFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
