#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STACK
#define STACK 1

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
    pNew->next = (*pTop);
    (*pTop) = pNew;
}
int pop(struct Node** pTop) {
    int retVal = INT_MIN;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        printf("Stack is Empty");
        return retVal;
    }
    retVal = pHead->data;
    (*pTop) = pHead->next;
    free(pHead);

    return retVal;
}
int peek(struct Node** pTop) {
    int retVal = INT_MIN;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        return retVal;
    }
    retVal = pHead->data;

    return retVal;
}
void stack_free(struct Node** pTop) {
    Node* pFree = (*pTop);
    while ((*pTop) != NULL) {
        (*pTop) = (*pTop)->next;
        free(pFree);
        pFree = (*pTop);
    }
}
#endif
typedef struct MyQueue {
    struct Node* inStack;
    struct Node* outStack;
} MyQueue;
MyQueue* myQueueCreate() {
    MyQueue* pRetVal = (MyQueue*)malloc(sizeof(struct MyQueue));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->inStack = NULL;
    pRetVal->outStack = NULL;

    return pRetVal;
}
void myQueuePush(MyQueue* obj, int x) {
    //
    push(&obj->inStack, x);
}
int myQueuePop(MyQueue* obj) {
    int retVal = INT_MIN;

    if ((obj->inStack == NULL) && (obj->outStack == NULL)) {
        return retVal;
    }

    if (obj->outStack == NULL) {
        while (obj->inStack != NULL) {
            retVal = pop(&obj->inStack);
            push(&obj->outStack, retVal);
        }
    }
    retVal = pop(&obj->outStack);

    return retVal;
}
int myQueuePeek(MyQueue* obj) {
    int retVal = INT_MIN;

    if ((obj->inStack == NULL) && (obj->outStack == NULL)) {
        return retVal;
    }

    if (obj->outStack == NULL) {
        while (obj->inStack != NULL) {
            retVal = pop(&obj->inStack);
            push(&obj->outStack, retVal);
        }
    }
    retVal = peek(&obj->outStack);

    return retVal;
}
bool myQueueEmpty(MyQueue* obj) {
    bool retVal = false;

    if ((obj->inStack == NULL) && (obj->outStack == NULL)) {
        retVal = true;
    }

    return retVal;
}
void myQueueFree(MyQueue* obj) {
    if (obj == NULL) {
        return;
    }
    stack_free(&obj->inStack);
    stack_free(&obj->outStack);
    free(obj);
}
/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);

 * int param_2 = myQueuePop(obj);

 * int param_3 = myQueuePeek(obj);

 * bool param_4 = myQueueEmpty(obj);

 * myQueueFree(obj);
*/

int main(int argc, char** argv) {
#define MAX_NUMSSIZE (100)
    struct testCaseType {
        char* methods[MAX_NUMSSIZE];
        int val[MAX_NUMSSIZE];
        int calls;
    } testCase[] = {
        {{"MyQueue", "push", "push", "peek", "pop", "empty"}, {INT_MIN, 1, 2, INT_MIN, INT_MIN, INT_MIN}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

#define STR_EMPTY ""
#define STR_COMMA ", "
    char displayStr[16];
    MyQueue* MyQueue;
    int retValue;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0 ? STR_EMPTY : STR_COMMA), testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            memset(displayStr, 0, sizeof(displayStr));
            snprintf(displayStr, sizeof(displayStr), "%d", testCase[i].val[j]);
            printf("%s[%s]", (j == 0 ? STR_EMPTY : STR_COMMA), (testCase[i].val[j] == INT_MIN) ? "" : displayStr);
        }
        printf("]\n");

        MyQueue = NULL;
        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "MyQueue") == 0) {
                MyQueue = myQueueCreate();
                printf("%s%s", "null", (j == (testCase[i].calls - 1) ? STR_EMPTY : STR_COMMA));
            } else if (strcmp(testCase[i].methods[j], "push") == 0) {
                myQueuePush(MyQueue, testCase[i].val[j]);
                printf("%s%s", "null", (j == (testCase[i].calls - 1) ? STR_EMPTY : STR_COMMA));
            } else if (strcmp(testCase[i].methods[j], "pop") == 0) {
                retValue = myQueuePop(MyQueue);
                printf("%d%s", retValue, (j == (testCase[i].calls - 1) ? STR_EMPTY : STR_COMMA));
            } else if (strcmp(testCase[i].methods[j], "peek") == 0) {
                retValue = myQueuePeek(MyQueue);
                printf("%d%s", retValue, (j == (testCase[i].calls - 1) ? STR_EMPTY : STR_COMMA));
            } else if (strcmp(testCase[i].methods[j], "empty") == 0) {
                retValue = myQueueEmpty(MyQueue);
                printf("%s%s", retValue ? "true" : "false", (j == (testCase[i].calls - 1) ? STR_EMPTY : STR_COMMA));
            }
        }
        printf("]\n");
        myQueueFree(MyQueue);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
