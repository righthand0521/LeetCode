#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/data-stream-as-disjoint-intervals/solutions/815374/shuang-xiang-lian-biao-by-chun-geng-0umq/
typedef struct SummaryRanges {
    int left;
    int right;
    struct SummaryRanges *pre;
    struct SummaryRanges *next;
} SummaryRanges;
SummaryRanges *summaryRangesCreate() {
    SummaryRanges *pRetVal = NULL;

    pRetVal = (SummaryRanges *)malloc(sizeof(SummaryRanges));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    SummaryRanges *pRear = (SummaryRanges *)malloc(sizeof(SummaryRanges));
    if (pRear == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    pRetVal->next = pRear;
    pRetVal->pre = pRear;
    pRetVal->left = 0;
    pRear->next = pRetVal;
    pRear->pre = pRetVal;

    return pRetVal;
}
SummaryRanges *insert(SummaryRanges *head, SummaryRanges *rear, int val) {
    SummaryRanges *pRetVal = NULL;

    SummaryRanges *pCurrent = head->next;
    while (pCurrent != rear) {
        if ((pCurrent->left <= val) && (val <= pCurrent->right)) {
            return pRetVal;
        } else if (pCurrent->right < val) {
            pCurrent = pCurrent->next;
        } else {
            break;
        }
    }

    pRetVal = (SummaryRanges *)malloc(sizeof(SummaryRanges));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->left = val;
    pRetVal->right = val;
    pRetVal->next = pCurrent;
    pRetVal->pre = pCurrent->pre;
    pCurrent->pre->next = pRetVal;
    pCurrent->pre = pRetVal;
    ++(head->left);

    return pRetVal;
}
void summaryRangesAddNum(SummaryRanges *obj, int val) {
    SummaryRanges *pHead = obj;
    SummaryRanges *pRear = obj->pre;

    SummaryRanges *p = insert(pHead, pRear, val);
    if (p == NULL) {
        return;
    }

    int f1 = ((p->pre != pHead) && (p->pre->right + 1 == p->left));
    int f2 = ((p->next != pRear) && (p->next->left - 1 == p->right));
    if (f1 && f2) {
        p->pre->right = p->next->right;
        p->pre->next = p->next->next;
        p->next->next->pre = p->pre;
        pHead->left -= 2;

        free(p->next);
        free(p);
    } else if (f1) {
        p->pre->right = p->right;
        p->pre->next = p->next;
        p->next->pre = p->pre;
        (pHead->left)--;
        free(p);
    } else if (f2) {
        p->next->left = p->left;
        p->next->pre = p->pre;
        p->pre->next = p->next;
        (pHead->left)--;
        free(p);
    }
}
int **summaryRangesGetIntervals(SummaryRanges *obj, int *retSize, int **retColSize) {
    int **pRetVal = NULL;

    (*retSize) = 0;

    SummaryRanges *pCurrent = obj->next;
    SummaryRanges *pRear = obj->pre;

    pRetVal = (int **)malloc((obj->left) * sizeof(int *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i;
    while (pCurrent != pRear) {
        pRetVal[(*retSize)] = (int *)malloc(2 * sizeof(int));
        if (pRetVal[(*retSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*retSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            (*retSize) = 0;
            return pRetVal;
        }
        pRetVal[(*retSize)][0] = pCurrent->left;
        pRetVal[(*retSize)][1] = pCurrent->right;
        (*retSize)++;

        pCurrent = pCurrent->next;
    }

    (*retColSize) = (int *)malloc((*retSize) * sizeof(int));
    if ((*retColSize) == NULL) {
        perror("malloc");
        for (i = 0; i < (*retSize); ++i) {
            free(pRetVal[i]);
            pRetVal[i] = NULL;
        }
        free(pRetVal);
        pRetVal = NULL;
        (*retSize) = 0;
        return pRetVal;
    }
    for (i = 0; i < (*retSize); ++i) {
        (*retColSize)[i] = 2;
    }

    return pRetVal;
}
void summaryRangesFree(SummaryRanges *obj) {
    SummaryRanges *pCurrent = obj->next;
    SummaryRanges *pRear = obj->pre;
    SummaryRanges *pTemp = NULL;
    while (pCurrent != pRear) {
        pTemp = pCurrent->next;
        free(pCurrent);
        pCurrent = pTemp;
    }
    free(pRear);
    free(obj);
}
/**
 * Your SummaryRanges struct will be instantiated and called as such:
 * SummaryRanges* obj = summaryRangesCreate();
 * summaryRangesAddNum(obj, value);
 * int** param_2 = summaryRangesGetIntervals(obj, retSize, retColSize);
 * summaryRangesFree(obj);
 */

int main(int argc, char **argv) {
#define MAX_SIZE (30000)
#define DISPLAY_NULL (-1)
    struct testCaseType {
        char *methods[MAX_SIZE];
        int value[MAX_SIZE];
        int calls;
    } testCase[] = {
        {{"SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum",
          "getIntervals", "addNum", "getIntervals"},
         {DISPLAY_NULL, 1, DISPLAY_NULL, 3, DISPLAY_NULL, 7, DISPLAY_NULL, 2, DISPLAY_NULL, 6, DISPLAY_NULL},
         11}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    SummaryRanges *obj = NULL;
    int **pRetVal = NULL;
    int retSize;
    int *retColSize = NULL;
    char buf[16];
    int row, col;
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
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%d", testCase[i].value[j]);
            printf("%s[%s]", (j == 0) ? "" : ", ", ((testCase[i].value[j] == DISPLAY_NULL) ? "" : buf));
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "SummaryRanges") == 0) {
                obj = summaryRangesCreate();
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "addNum") == 0) {
                summaryRangesAddNum(obj, testCase[i].value[j]);
                printf("%snull", (j == 0) ? "" : ", ");
            } else if (strcmp(testCase[i].methods[j], "getIntervals") == 0) {
                pRetVal = summaryRangesGetIntervals(obj, &retSize, &retColSize);
                printf("%s[", (j == 0) ? "" : ", ");
                for (row = 0; row < retSize; ++row) {
                    printf("%s[", (row == 0 ? "" : ", "));
                    for (col = 0; col < retColSize[row]; ++col) {
                        printf("%s%d", (col == 0 ? "" : ", "), pRetVal[row][col]);
                    }
                    printf("]");
                }
                printf("]");

                free(retColSize);
                retColSize = NULL;
                for (row = 0; row < retSize; ++row) {
                    free(pRetVal[row]);
                    pRetVal[row] = NULL;
                }
                free(pRetVal);
                pRetVal = NULL;
            }
        }
        printf("]\n");

        summaryRangesFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
