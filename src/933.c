#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* queue;
    int capability;
    int head;
    int tail;
} RecentCounter;
RecentCounter* recentCounterCreate() {
    RecentCounter* pObj = NULL;

    pObj = (RecentCounter*)malloc(sizeof(RecentCounter));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->capability = 10001;  // At most 10^4 calls will be made to ping.
    pObj->queue = (int*)malloc(sizeof(int) * pObj->capability);
    if (pObj->queue == NULL) {
        perror("malloc");
        free(pObj);
        pObj = NULL;
        return pObj;
    }
    pObj->head = 0;
    pObj->tail = 0;

    return pObj;
}
int recentCounterPing(RecentCounter* obj, int t) {
    int retVal = 0;

    obj->queue[obj->tail++] = t;
    while (obj->queue[obj->head] < t - 3000) {
        obj->head++;
    }
    retVal = obj->tail - obj->head;

    return retVal;
}
void recentCounterFree(RecentCounter* obj) {
    free(obj->queue);
    obj->queue = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your RecentCounter struct will be instantiated and called as such:
 * RecentCounter* obj = recentCounterCreate();
 * int param_1 = recentCounterPing(obj, t);
 * recentCounterFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE];
        int calls;
    } testCase[] = {{{"RecentCounter", "ping", "ping", "ping", "ping"}, {0, 1, 100, 3001, 3002}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["RecentCounter", "ping", "ping", "ping", "ping"]
     *  [[], [1], [100], [3001], [3002]]
     *  Output
     *  [null, 1, 2, 3, 3]
     */

    RecentCounter* obj = NULL;
    int retInt;
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
            if (j == 0) {
                printf("[]");
            } else {
                printf("%s[%d]", (j == 0) ? "" : ", ", testCase[i].val[j]);
            }
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            memset(displayStr, 0, sizeof(displayStr));
            if (strcmp(testCase[i].methods[j], "RecentCounter") == 0) {
                obj = recentCounterCreate();
                snprintf(displayStr, sizeof(displayStr), "%s", "null");
            } else if (strcmp(testCase[i].methods[j], "ping") == 0) {
                retInt = recentCounterPing(obj, testCase[i].val[j]);
                snprintf(displayStr, sizeof(displayStr), "%d", retInt);
            }
            printf("%s%s", (j == 0) ? "" : ", ", displayStr);
        }
        printf("]\n");

        recentCounterFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
