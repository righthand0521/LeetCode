#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DLinkListNode {
    int val;
    struct DLinkListNode* prev;
    struct DLinkListNode* next;
} DLinkListNode;
DLinkListNode* dLinkListNodeCreat(int val) {
    DLinkListNode* obj = NULL;

    obj = (DLinkListNode*)malloc(sizeof(DLinkListNode));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->val = val;
    obj->prev = NULL;
    obj->next = NULL;

    return obj;
}
typedef struct {
    int capacity;
    DLinkListNode* head;
    DLinkListNode* tail;
    int size;
} MyCircularDeque;
MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque* obj = NULL;

    obj = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->capacity = k;
    obj->head = NULL;
    obj->tail = NULL;
    obj->size = 0;

    return obj;
}
bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    bool retVal = false;

    if (obj->size == 0) {
        retVal = true;
    }

    return retVal;
}
bool myCircularDequeIsFull(MyCircularDeque* obj) {
    bool retVal = false;

    if (obj->size == obj->capacity) {
        retVal = true;
    }

    return retVal;
}
bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    bool retVal = false;

    if (myCircularDequeIsFull(obj) == true) {
        return retVal;
    }

    DLinkListNode* pNew = dLinkListNodeCreat(value);
    if (pNew == NULL) {
        return retVal;
    }

    if (obj->size == 0) {
        obj->head = pNew;
        obj->tail = pNew;
    } else {
        pNew->next = obj->head;
        obj->head->prev = pNew;
        obj->head = pNew;
    }
    obj->size++;
    retVal = true;

    return retVal;
}
bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    bool retVal = false;

    if (myCircularDequeIsFull(obj) == true) {
        return retVal;
    }

    DLinkListNode* pNew = dLinkListNodeCreat(value);
    if (pNew == NULL) {
        return retVal;
    }

    if (obj->size == 0) {
        obj->head = pNew;
        obj->tail = pNew;
    } else {
        obj->tail->next = pNew;
        pNew->prev = obj->tail;
        obj->tail = pNew;
    }
    obj->size++;
    retVal = true;

    return retVal;
}
bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    bool retVal = false;

    if (myCircularDequeIsEmpty(obj) == true) {
        return retVal;
    }

    DLinkListNode* pDelete = obj->head;
    obj->head = obj->head->next;
    if (obj->head != NULL) {
        obj->head->prev = NULL;
    }
    free(pDelete);
    pDelete = NULL;
    obj->size--;
    retVal = true;

    return retVal;
}
bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    bool retVal = false;

    if (myCircularDequeIsEmpty(obj) == true) {
        return retVal;
    }

    DLinkListNode* pDelete = obj->tail;
    obj->tail = obj->tail->prev;
    if (obj->tail != NULL) {
        obj->tail->next = NULL;
    }
    free(pDelete);
    pDelete = NULL;
    obj->size--;
    retVal = true;

    return retVal;
}
int myCircularDequeGetFront(MyCircularDeque* obj) {
    int retVal = -1;  // Returns -1 if the deque is empty.

    if (myCircularDequeIsEmpty(obj) == false) {
        retVal = obj->head->val;
    }

    return retVal;
}
int myCircularDequeGetRear(MyCircularDeque* obj) {
    int retVal = -1;  // Returns -1 if the deque is empty.

    if (myCircularDequeIsEmpty(obj) == false) {
        retVal = obj->tail->val;
    }

    return retVal;
}
void myCircularDequeFree(MyCircularDeque* obj) {
    DLinkListNode* pDelete = NULL;
    while (obj->head != obj->tail) {
        pDelete = obj->head;
        obj->head = obj->head->next;
        free(pDelete);
        pDelete = NULL;
    }
    free(obj->head);
    obj->head = NULL;

    free(obj);
    obj = NULL;
}
/**
 * Your MyCircularDeque struct will be instantiated and called as such:
 * MyCircularDeque* obj = myCircularDequeCreate(k);
 * bool param_1 = myCircularDequeInsertFront(obj, value);
 * bool param_2 = myCircularDequeInsertLast(obj, value);
 * bool param_3 = myCircularDequeDeleteFront(obj);
 * bool param_4 = myCircularDequeDeleteLast(obj);
 * int param_5 = myCircularDequeGetFront(obj);
 * int param_6 = myCircularDequeGetRear(obj);
 * bool param_7 = myCircularDequeIsEmpty(obj);
 * bool param_8 = myCircularDequeIsFull(obj);
 * myCircularDequeFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][1];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"MyCircularDeque", "insertLast", "insertLast", "insertFront", "insertFront", "getRear", "isFull",
                      "deleteLast", "insertFront", "getFront"},
                     {{3}, {1}, {2}, {3}, {4}, {}, {}, {}, {4}, {}},
                     {1, 1, 1, 1, 1, 0, 0, 0, 1, 0},
                     10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["MyCircularDeque", "insertLast", "insertLast", "insertFront", "insertFront",
     *  "getRear", "isFull", "deleteLast", "insertFront", "getFront"]
     *  [[3], [1], [2], [3], [4], [], [], [], [4], []]
     *  Output
     *  [null, true, true, true, false, 2, true, true, true, 4]
     */

    MyCircularDeque* obj = NULL;
    bool boolRetVal;
    int inRetVal;
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
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].val[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s", (j == 0) ? "" : ",");

            if (strcmp(testCase[i].methods[j], "MyCircularDeque") == 0) {
                obj = myCircularDequeCreate(testCase[i].val[j][0]);
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "insertFront") == 0) {
                boolRetVal = myCircularDequeInsertFront(obj, testCase[i].val[j][0]);
                printf("%s%s", (j == 0) ? "" : " ", (boolRetVal == true ? "true" : "false"));
            } else if (strcmp(testCase[i].methods[j], "insertLast") == 0) {
                boolRetVal = myCircularDequeInsertLast(obj, testCase[i].val[j][0]);
                printf("%s%s", (j == 0) ? "" : " ", (boolRetVal == true ? "true" : "false"));
            } else if (strcmp(testCase[i].methods[j], "deleteFront") == 0) {
                boolRetVal = myCircularDequeDeleteFront(obj);
                printf("%s%s", (j == 0) ? "" : " ", (boolRetVal == true ? "true" : "false"));
            } else if (strcmp(testCase[i].methods[j], "deleteLast") == 0) {
                boolRetVal = myCircularDequeDeleteLast(obj);
                printf("%s%s", (j == 0) ? "" : " ", (boolRetVal == true ? "true" : "false"));
            } else if (strcmp(testCase[i].methods[j], "getFront") == 0) {
                inRetVal = myCircularDequeGetFront(obj);
                printf("%s%d", (j == 0) ? "" : " ", inRetVal);
            } else if (strcmp(testCase[i].methods[j], "getRear") == 0) {
                inRetVal = myCircularDequeGetRear(obj);
                printf("%s%d", (j == 0) ? "" : " ", inRetVal);
            } else if (strcmp(testCase[i].methods[j], "isEmpty") == 0) {
                boolRetVal = myCircularDequeIsEmpty(obj);
                printf("%s%s", (j == 0) ? "" : " ", (boolRetVal == true ? "true" : "false"));
            } else if (strcmp(testCase[i].methods[j], "isFull") == 0) {
                boolRetVal = myCircularDequeIsFull(obj);
                printf("%s%s", (j == 0) ? "" : " ", (boolRetVal == true ? "true" : "false"));
            }
        }
        printf("]\n");

        myCircularDequeFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
