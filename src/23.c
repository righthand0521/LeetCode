#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int mergeTwoList(struct ListNode* pList, struct ListNode* qList) {
    struct ListNode* pRetVal = NULL;
    struct ListNode* p = pList;
    struct ListNode* q = qList;

    int idx = 0;
    bool flag = false;
    struct ListNode* pHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pHead == NULL) {
        perror("malloc");
        return idx;
    }
    pHead->val = 0;
    pHead->next = NULL;
    pRetVal = pHead;

    while ((p != NULL) || (q != NULL)) {
        if (p == NULL) {
            if (flag == false) {
                idx = 1;
                flag = true;
            }
            pHead->next = q;
            q = q->next;
            pHead = pHead->next;
        } else if (q == NULL) {
            if (flag == false) {
                idx = 0;
                flag = true;
            }
            pHead->next = p;
            p = p->next;
            pHead = pHead->next;
        } else if (p->val <= q->val) {
            if (flag == false) {
                idx = 0;
                flag = true;
            }
            pHead->next = p;
            p = p->next;
            pHead = pHead->next;
        } else if (p->val > q->val) {
            if (flag == false) {
                idx = 1;
                flag = true;
            }
            pHead->next = q;
            q = q->next;
            pHead = pHead->next;
        }
    }
    pHead = pRetVal;
    pRetVal = pHead->next;
    pHead->next = NULL;
    free(pHead);
    pHead = NULL;

    return idx;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    struct ListNode* pRetVal = NULL;

    if (listsSize == 0) {
        return pRetVal;
    }

    int ret = 0;
    struct ListNode* p = NULL;
    struct ListNode* q = NULL;
    int i;
    while (listsSize > 1) {
        for (i = 0; i < listsSize; i += 2) {
            p = lists[i];
            if (i + 1 >= listsSize) {
                lists[i / 2] = lists[i];
                break;
            }
            q = lists[i + 1];

            ret = mergeTwoList(p, q);
            lists[i / 2] = lists[i + ret];
        }
        listsSize = (listsSize % 2 == 1) ? (listsSize / 2 + 1) : listsSize / 2;
    }
    pRetVal = lists[0];

    return pRetVal;
}

int main(int argc, char** argv) {
#define TEST_USED 100
#define MAX_LISTS_SIZE (10000 / TEST_USED)
#define MAX_LISTS_LENGTH (500 / TEST_USED)
    struct testCaseType {
        int lists[MAX_LISTS_SIZE][MAX_LISTS_LENGTH];
        int listsSize;
    } testCase[] = {{{{1, 4, 5}, {1, 3, 4}, {2, 6}}, 3},        {{}, 0}, {{{}}, 1}, {{{}, {1}}, 2}, {{{1}, {}}, 2},
                    {{{1, 4, 5}, {1, 3, 4}, {2, 6}, {7, 8}}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: lists = [[1,4,5],[1,3,4],[2,6]]
     *  Output: [1,1,2,3,4,4,5,6]
     *
     *  Input: lists = []
     *  Output: []
     *
     *  Input: lists = [[]]
     *  Output: []
     */

    struct ListNode* pAnswer;
    struct ListNode* pList;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        struct ListNode* lists[testCase[i].listsSize];
        printf("Input: lists = [");
        for (j = 0; j < testCase[i].listsSize; ++j) {
            pList = NULL;
            for (k = 0; k < MAX_LISTS_LENGTH; ++k) {
                if (testCase[i].lists[j][k] == 0) {
                    break;
                }
                pList = addValueToEndListNode(pList, testCase[i].lists[j][k]);
            }
            printf("[");
            printList(pList);
            printf("]%s", (j == testCase[i].listsSize - 1) ? "" : ",");

            lists[j] = pList;
        }
        printf("]\n");

        pAnswer = mergeKLists(lists, testCase[i].listsSize);
        printf("Output: [");
        printList(pAnswer);
        printf("]\n");

        printf("\n");

        if (pAnswer == NULL) {
            continue;
        }
        freeListNode(lists[0]);
    }

    return EXIT_SUCCESS;
}
