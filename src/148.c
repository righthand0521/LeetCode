#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define QUICK_SORT (1)
#define ADD (1)  // Time Limit Exceeded
#if (QUICK_SORT)
int cmp_LinkedNode(const void* a, const void* b) {
    const struct ListNode* const* aa = a;
    const struct ListNode* const* bb = b;
    return ((*aa)->val > (*bb)->val) - ((*aa)->val < (*bb)->val);
}
#elif (ADD)
struct ListNode* addValueToMiddle(struct ListNode* pHead, int value) {
    struct ListNode* pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->val = value;
    pNew->next = NULL;

    if (pHead == NULL) {
        pHead = pNew;
        return pHead;
    }

    struct ListNode* pPrevious = NULL;
    struct ListNode* pCurrent = pHead;
    while (pCurrent != NULL) {
        // from small to large
        if (pCurrent->val > value) {
            break;
        }
        pPrevious = pCurrent;
        pCurrent = pCurrent->next;
    }
    if (pPrevious == NULL) {
        pNew->next = pHead;
        pHead = pNew;
        return pHead;
    }
    pNew->next = pPrevious->next;
    pPrevious->next = pNew;

    return pHead;
}
#endif
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* sortList(struct ListNode* head) {
    struct ListNode* pRetVal = NULL;

#if (QUICK_SORT)
    printf("QUICK_SORT\n");

    if ((head == NULL) || (head->next == NULL)) {
        return head;
    }

    int size_of_list = 0;
    struct ListNode* p;
    for (p = head; p != NULL; p = p->next) {
        ++size_of_list;
    }

    struct ListNode* arr[size_of_list + 1];
    struct ListNode** arrp = arr;
    for (p = head; p != NULL; p = p->next) {
        *arrp++ = p;
    }
    *arrp = NULL;
    qsort(arr, size_of_list, sizeof(*arr), cmp_LinkedNode);

    int i;
    for (i = 0; i < size_of_list; ++i) {
        arr[i]->next = arr[i + 1];
    }
    head = arr[0];
    pRetVal = arr[0];
#elif (ADD)
    printf("ADD\n");

    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        pRetVal = addValueToMiddle(pRetVal, pCurrent->val);
        pCurrent = pCurrent->next;
    }
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_NODES (5 * 10000)
    struct testCaseType {
        int node[MAX_NODES];
        int nodeSize;
    } testCase[] = {{{4, 2, 1, 3}, 4}, {{-1, 5, 3, 4, 0}, 5}, {{}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [4,2,1,3]
     *  Output: [1,2,3,4]
     *
     *  Input: head = [-1,5,3,4,0]
     *  Output: [-1,0,3,4,5]
     *
     *  Input: head = []
     *  Output: []
     */

    struct ListNode* pHead = NULL;
    struct ListNode* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        for (j = 0; j < testCase[i].nodeSize; ++j) {
            pHead = addValueToEndListNode(pHead, testCase[i].node[j]);
        }
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pAnswer = sortList(pHead);
        printf("Output: [");
        printList(pAnswer);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
#if (QUICK_SORT)
#elif (ADD)
        freeListNode(pAnswer);
        pAnswer = NULL;
#endif
    }

    return EXIT_SUCCESS;
}
