#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE (1)
#if (QUEUE)
typedef struct Node {
    int data;
    struct Node* next;
} Node;
void push(struct Node** pTop, int value) {
    Node* pNew = (Node*)malloc(sizeof(struct Node));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->data = value;
    pNew->next = NULL;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        (*pTop) = pNew;
        return;
    }

    while (pHead->next != NULL) {
        pHead = pHead->next;
    }
    pHead->next = pNew;
}
int pop(struct Node** pTop) {
    int retVal = 0;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        printf("Queue is Empty");
        return retVal;
    }
    retVal = pHead->data;
    (*pTop) = pHead->next;
    free(pHead);

    return retVal;
}
int peek(struct Node** pTop) {
    int retVal = 0;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        return retVal;
    }
    retVal = pHead->data;

    return retVal;
}
#endif
typedef struct MyStack {
    struct Node* useQueue;
    struct Node* tempQueue;
} MyStack;
MyStack* myStackCreate() {
    MyStack* pRetVal = (MyStack*)malloc(sizeof(struct MyStack));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->useQueue = NULL;
    pRetVal->tempQueue = NULL;

    return pRetVal;
}
void myStackPush(MyStack* obj, int x) {
    //
    push(&obj->useQueue, x);
}
int myStackPop(MyStack* obj) {
    int retVal = 0;

    if (obj->useQueue == NULL) {
        return retVal;
    }

    while (obj->useQueue->next != NULL) {
        retVal = pop(&obj->useQueue);
        push(&obj->tempQueue, retVal);
    }
    retVal = pop(&obj->useQueue);

    struct Node* pTmp = obj->useQueue;
    obj->useQueue = obj->tempQueue;
    obj->tempQueue = pTmp;

    return retVal;
}
int myStackTop(MyStack* obj) {
    int retVal = 0;

    if (obj->useQueue == NULL) {
        return retVal;
    }

    while (obj->useQueue->next != NULL) {
        retVal = pop(&obj->useQueue);
        push(&obj->tempQueue, retVal);
    }
    retVal = pop(&obj->useQueue);
    push(&obj->tempQueue, retVal);

    struct Node* pTmp = obj->useQueue;
    obj->useQueue = obj->tempQueue;
    obj->tempQueue = pTmp;

    return retVal;
}
bool myStackEmpty(MyStack* obj) {
    bool retVal = false;

    if ((obj->useQueue == NULL) && (obj->tempQueue == NULL)) {
        retVal = true;
    }

    return retVal;
}
void myStackFree(MyStack* obj) {
    free(obj->useQueue);
    obj->useQueue = NULL;
    free(obj->tempQueue);
    obj->tempQueue = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 * int param_2 = myStackPop(obj);
 * int param_3 = myStackTop(obj);
 * bool param_4 = myStackEmpty(obj);
 * myStackFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][1];
        int calls;
    } testCase[] = {{{"MyStack", "push", "push", "top", "pop", "empty"}, {{}, {1}, {2}, {}, {}, {}}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["MyStack", "push", "push", "top", "pop", "empty"]
     *  [[], [1], [2], [], [], []]
     *  Output
     *  [null, null, null, 2, 2, false]
     */

    MyStack* obj = NULL;
    int retInt;
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
            if (strcmp(testCase[i].methods[j], "MyStack") == 0) {
                obj = myStackCreate();
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "push") == 0) {
                myStackPush(obj, testCase[i].val[j][0]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "pop") == 0) {
                retInt = myStackPop(obj);
                printf("%s%d", (j == 0) ? "" : ", ", retInt);
            } else if (strcmp(testCase[i].methods[j], "top") == 0) {
                retInt = myStackTop(obj);
                printf("%s%d", (j == 0) ? "" : ", ", retInt);
            } else if (strcmp(testCase[i].methods[j], "empty") == 0) {
                retBool = myStackEmpty(obj);
                printf("%s%s", (j == 0) ? "" : ", ", (retBool == true ? "true" : "false"));
            }
        }
        printf("]\n");

        myStackFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
