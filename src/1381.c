#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    int top;
    int maxSize;
} CustomStack;
CustomStack* customStackCreate(int maxSize) {
    CustomStack* obj = NULL;

    obj = (CustomStack*)malloc(sizeof(CustomStack));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->data = (int*)malloc(maxSize * sizeof(int));
    if (obj->data == NULL) {
        perror("malloc");
        return obj;
    }
    obj->maxSize = maxSize;
    obj->top = -1;  // Pops and returns the top of the stack or -1 if the stack is empty.

    return obj;
}
void customStackPush(CustomStack* obj, int x) {
    if (obj->top == obj->maxSize - 1) {
        return;
    }
    obj->top += 1;
    obj->data[obj->top] = x;
}
int customStackPop(CustomStack* obj) {
    int retVal = -1;  // Pops and returns the top of the stack or -1 if the stack is empty.

    if (obj->top == -1) {
        return retVal;
    }
    retVal = obj->data[obj->top];
    obj->top -= 1;

    return retVal;
}
void customStackIncrement(CustomStack* obj, int k, int val) {
    int i;
    if (obj->top + 1 < k) {
        for (i = 0; i <= obj->top; i++) {
            obj->data[i] += val;
        }
    } else {
        for (i = 0; i < k; i++) {
            obj->data[i] += val;
        }
    }
}
void customStackFree(CustomStack* obj) {
    free(obj->data);
    obj->data = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your CustomStack struct will be instantiated and called as such:
 * CustomStack* obj = customStackCreate(maxSize);
 * customStackPush(obj, x);
 * int param_2 = customStackPop(obj);
 * customStackIncrement(obj, k, val);
 * customStackFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][2];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"CustomStack", "push", "push", "pop", "push", "push", "push", "increment", "increment", "pop",
                      "pop", "pop", "pop"},
                     {{3}, {1}, {2}, {}, {2}, {3}, {4}, {5, 100}, {2, 100}, {}, {}, {}, {}},
                     {1, 1, 1, 0, 1, 1, 1, 2, 2, 0, 0, 0, 0},
                     13}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["CustomStack","push","push","pop","push","push","push","increment","increment","pop","pop","pop","pop"]
     *  [[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[],[]]
     *  Output
     *  [null,null,null,2,null,null,null,null,null,103,202,201,-1]
     */

    CustomStack* obj = NULL;
    int retVal;
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

            if (strcmp(testCase[i].methods[j], "CustomStack") == 0) {
                obj = customStackCreate(testCase[i].val[j][0]);
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "push") == 0) {
                customStackPush(obj, testCase[i].val[j][0]);
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "pop") == 0) {
                retVal = customStackPop(obj);
                printf("%s%d", (j == 0) ? "" : " ", retVal);
            } else if (strcmp(testCase[i].methods[j], "increment") == 0) {
                customStackIncrement(obj, testCase[i].val[j][0], testCase[i].val[j][1]);
                printf("null");
            }
        }
        printf("]\n");

        customStackFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
