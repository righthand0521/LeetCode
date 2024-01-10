#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int first;
    int second;
    struct Node *next;
} Node;
typedef struct {
    Node *stack;
    int idx;
} StockSpanner;
Node *nodeCreate(int first, int second) {
    Node *pRetVal = NULL;

    pRetVal = (Node *)malloc(sizeof(Node));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->first = first;
    pRetVal->second = second;
    pRetVal->next = NULL;

    return pRetVal;
}
StockSpanner *stockSpannerCreate() {
    StockSpanner *pRetVal = NULL;

    pRetVal = (StockSpanner *)malloc(sizeof(StockSpanner));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->idx = -1;
    pRetVal->stack = nodeCreate(-1, INT_MAX);

    return pRetVal;
}
int stockSpannerNext(StockSpanner *obj, int price) {
    int retVal = 0;

    obj->idx++;

    Node *pTmp = NULL;
    while (price >= obj->stack->second) {
        pTmp = obj->stack;
        obj->stack = obj->stack->next;
        free(pTmp);
        pTmp = NULL;
    }

    retVal = obj->idx - obj->stack->first;
    pTmp = nodeCreate(obj->idx, price);
    if (pTmp == NULL) {
        return retVal;
    }
    pTmp->next = obj->stack;
    obj->stack = pTmp;

    return retVal;
}
void stockSpannerFree(StockSpanner *obj) {
    Node *pFree = NULL;
    Node *pTmp = NULL;
    for (pTmp = obj->stack; pTmp != NULL;) {
        pFree = pTmp;
        pTmp = pTmp->next;
        free(pFree);
        pFree = NULL;
    }
    free(obj);
    obj = NULL;
}
/**
 * Your StockSpanner struct will be instantiated and called as such:
 * StockSpanner* obj = stockSpannerCreate();
 * int param_1 = stockSpannerNext(obj, price);
 * stockSpannerFree(obj);
 */

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char *methods[MAX_SIZE];
        int val[MAX_SIZE];
        int calls;
    } testCase[] = {{{"StockSpanner", "next", "next", "next", "next", "next", "next", "next"},
                     {INT_MIN, 100, 80, 60, 70, 60, 75, 85},
                     8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
     *  [[], [100], [80], [60], [70], [60], [75], [85]]
     *  Output
     *  [null, 1, 1, 1, 2, 1, 4, 6]
     */

    StockSpanner *obj = NULL;
    int retInt;
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
            if (strcmp(testCase[i].methods[j], "StockSpanner") == 0) {
                obj = stockSpannerCreate();
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "next") == 0) {
                retInt = stockSpannerNext(obj, testCase[i].val[j]);
                printf("%s%d", (j == 0) ? "" : ", ", retInt);
            }
        }
        printf("]\n");

        stockSpannerFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
