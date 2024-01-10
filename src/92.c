#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
    struct ListNode* pRetVal = head;

    struct ListNode* pTmp = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pTmp == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pTmp->val = -1;
    pTmp->next = head;

    int i;

    struct ListNode* pPrevious = pTmp;
    for (i = 0; i < left - 1; ++i) {
        pPrevious = pPrevious->next;
    }

    struct ListNode* pCurrent = pPrevious->next;

    struct ListNode* pNext;
    for (i = left; i < right; ++i) {
        pNext = pCurrent->next;
        pCurrent->next = pNext->next;
        pNext->next = pPrevious->next;
        pPrevious->next = pNext;
    }

    pRetVal = pTmp->next;
    free(pTmp);
    pTmp = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_NODES (500)
    struct testCaseType {
        int node[MAX_NODES];
        int nodeSize;
        int left;
        int right;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5, 2, 4}, {{5}, 1, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,3,4,5], left = 2, right = 4
     *  Output: [1,4,3,2,5]
     *
     *  Input: head = [5], left = 1, right = 1
     *  Output: [5]
     */

    struct ListNode* pHead = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pHead = reverseBetween(pHead, testCase[i].left, testCase[i].right);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
