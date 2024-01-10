#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int size;
    int head;
    int tail;
    int count;
    int* value;
} MyCircularQueue;
MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue* pNew = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->size = k;
    pNew->head = 0;
    pNew->tail = 0;
    pNew->count = 0;
    pNew->value = (int*)malloc(pNew->size * sizeof(int));
    if (pNew->value == NULL) {
        perror("malloc");
        return pNew;
    }
    memset(pNew->value, 0, (pNew->size * sizeof(int)));

    return pNew;
}
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    if (obj->count == 0) {
        return true;
    }
    return false;
}
bool myCircularQueueIsFull(MyCircularQueue* obj) {
    if (obj->count == obj->size) {
        return true;
    }
    return false;
}
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (myCircularQueueIsFull(obj) == true) {
        return false;
    }
    obj->count++;
    obj->value[obj->tail] = value;
    obj->tail = (obj->tail + 1) % obj->size;
    return true;
}
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj) == true) {
        return false;
    }
    obj->count--;
    obj->value[obj->head] = 0;
    obj->head = (obj->head + 1) % obj->size;
    return true;
}
int myCircularQueueFront(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj) == true) {
        return -1;
    }
    return obj->value[obj->head];
}
int myCircularQueueRear(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj) == true) {
        return -1;
    }
    return obj->value[(obj->tail - 1 + obj->size) % obj->size];
}
void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj->value);
    obj->value = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);

 * bool param_2 = myCircularQueueDeQueue(obj);

 * int param_3 = myCircularQueueFront(obj);

 * int param_4 = myCircularQueueRear(obj);

 * bool param_5 = myCircularQueueIsEmpty(obj);

 * bool param_6 = myCircularQueueIsFull(obj);

 * myCircularQueueFree(obj);
*/

int main(int argc, char** argv) {
#define MAX_SIZE (32)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE];
        int calls;
    } testCase[] = {{{"MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear", "isFull", "deQueue",
                      "enQueue", "Rear"},
                     {3, 1, 2, 3, 4, INT_MIN, INT_MIN, INT_MIN, 4, INT_MIN},
                     10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    MyCircularQueue* obj = NULL;
    int retInt;
    bool retBool;
    char displayStr[8];
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
            if (testCase[i].val[j] == INT_MIN) {
                printf("%s[]", (j == 0) ? "" : ", ");
                continue;
            }
            printf("%s[%d]", (j == 0) ? "" : ", ", testCase[i].val[j]);
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            memset(displayStr, 0, sizeof(displayStr));
            if (strcmp(testCase[i].methods[j], "MyCircularQueue") == 0) {
                obj = myCircularQueueCreate(testCase[i].val[j]);
                snprintf(displayStr, sizeof(displayStr), "%s", "null");
            } else if (strcmp(testCase[i].methods[j], "Front") == 0) {
                retInt = myCircularQueueFront(obj);
                snprintf(displayStr, sizeof(displayStr), "%d", retInt);
            } else if (strcmp(testCase[i].methods[j], "Rear") == 0) {
                retInt = myCircularQueueRear(obj);
                snprintf(displayStr, sizeof(displayStr), "%d", retInt);
            } else if (strcmp(testCase[i].methods[j], "enQueue") == 0) {
                retBool = myCircularQueueEnQueue(obj, testCase[i].val[j]);
                snprintf(displayStr, sizeof(displayStr), "%s", (retBool == true) ? "true" : "false");
            } else if (strcmp(testCase[i].methods[j], "deQueue") == 0) {
                retBool = myCircularQueueDeQueue(obj);
                snprintf(displayStr, sizeof(displayStr), "%s", (retBool == true) ? "true" : "false");
            } else if (strcmp(testCase[i].methods[j], "isEmpty") == 0) {
                retBool = myCircularQueueIsEmpty(obj);
                snprintf(displayStr, sizeof(displayStr), "%s", (retBool == true) ? "true" : "false");
            } else if (strcmp(testCase[i].methods[j], "isFull") == 0) {
                retBool = myCircularQueueIsFull(obj);
                snprintf(displayStr, sizeof(displayStr), "%s", (retBool == true) ? "true" : "false");
            }
            printf("%s%s", (j == 0) ? "" : ", ", displayStr);
        }
        printf("]\n");

        myCircularQueueFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
