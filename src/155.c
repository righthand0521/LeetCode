#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MinStack {
    int data;
    int min;
    struct MinStack *next;
} MinStack;
MinStack *top = NULL;
void show() {
    MinStack *pHead = top;
    while (pHead != NULL) {
        printf("[%d|%d] -> ", pHead->data, pHead->min);
        pHead = pHead->next;
    }
    printf("NULL\n");
}
MinStack *minStackCreate() {
    MinStack *pRetVal = (MinStack *)malloc(sizeof(struct MinStack));
    if (pRetVal == NULL) {
        perror("malloc");
    }

    return pRetVal;
}
void minStackPush(MinStack *obj, int val) {
    MinStack *pNew = (MinStack *)malloc(sizeof(struct MinStack));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->data = val;
    pNew->min = val;
    if ((top != NULL) && (val > top->min)) {
        pNew->min = top->min;
    }
    pNew->next = top;
    top = pNew;
}
void minStackPop(MinStack *obj) {
    MinStack *pHead = top;
    if (pHead == NULL) {
        return;
    }
    top = pHead->next;
    free(pHead);
}
int minStackTop(MinStack *obj) {
    int retVal = INT_MIN;

    MinStack *pHead = top;
    if (pHead == NULL) {
        return retVal;
    }
    retVal = pHead->data;

    return retVal;
}
int minStackGetMin(MinStack *obj) {
    int retVal = INT_MIN;

    MinStack *pHead = top;
    if (pHead == NULL) {
        return retVal;
    }
    retVal = pHead->min;

    return retVal;
}
void minStackFree(MinStack *obj) {
    free(obj);
    top = NULL;
}

int main(int argc, char **argv) {
#define MAX_NUMSSIZE (3 * 10000)
    struct testCaseType {
        char *methods[MAX_NUMSSIZE];
        int val[MAX_NUMSSIZE];
        int calls;
    } testCase[] = {{{"MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"},
                     {INT_MIN, -2, 0, -3, INT_MIN, INT_MIN, INT_MIN, INT_MIN},
                     8},
                    {{"MinStack", "push", "top", "getMin"}, {INT_MIN, -1, INT_MIN, INT_MIN}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char displayStr[16];
    MinStack *minStack;
    int retValue;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("\"%s\"%s", testCase[i].methods[j], (j == (testCase[i].calls - 1) ? "" : ","));
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            memset(displayStr, 0, sizeof(displayStr));
            snprintf(displayStr, sizeof(displayStr), "%d", testCase[i].val[j]);
            printf("[%s]%s", (testCase[i].val[j] == INT_MIN) ? "" : displayStr,
                   (j == (testCase[i].calls - 1) ? "" : ","));
        }
        printf("]\n");

        minStack = NULL;
        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "MinStack") == 0) {
                minStack = minStackCreate();
                printf("%s%s", "null", (j == (testCase[i].calls - 1) ? "" : ","));
            } else if (strcmp(testCase[i].methods[j], "push") == 0) {
                minStackPush(minStack, testCase[i].val[j]);
                printf("%s%s", "null", (j == (testCase[i].calls - 1) ? "" : ","));
            } else if (strcmp(testCase[i].methods[j], "pop") == 0) {
                minStackPop(minStack);
                printf("%s%s", "null", (j == (testCase[i].calls - 1) ? "" : ","));
            } else if (strcmp(testCase[i].methods[j], "top") == 0) {
                retValue = minStackTop(minStack);
                printf("%d%s", retValue, (j == (testCase[i].calls - 1) ? "" : ","));
            } else if (strcmp(testCase[i].methods[j], "getMin") == 0) {
                retValue = minStackGetMin(minStack);
                printf("%d%s", retValue, (j == (testCase[i].calls - 1) ? "" : ","));
            }
        }
        printf("]\n");
        minStackFree(minStack);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
