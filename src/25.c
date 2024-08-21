#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void reverse(struct ListNode** head, struct ListNode** tail) {
    struct ListNode* pPrevious = (*tail)->next;
    struct ListNode* pCurrent = (*head);
    struct ListNode* pNext;
    while (pPrevious != (*tail)) {
        pNext = pCurrent->next;
        pCurrent->next = pPrevious;
        pPrevious = pCurrent;
        pCurrent = pNext;
    }

    struct ListNode* pTmp = (*head);
    (*head) = (*tail);
    (*tail) = pTmp;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode* pRetVal = head;

    struct ListNode* pHair = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pHair == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pHair->val = 0;
    pHair->next = head;

    struct ListNode* pPrevious = pHair;

    struct ListNode* pNext;
    struct ListNode* pTail;
    int i;
    while (head != NULL) {
        pTail = pPrevious;

        for (i = 0; i < k; ++i) {
            pTail = pTail->next;
            if (pTail == NULL) {
                pRetVal = pHair->next;
                free(pHair);
                pHair = NULL;
                return pRetVal;
            }
        }

        pNext = pTail->next;
        reverse(&head, &pTail);
        pPrevious->next = head;
        pTail->next = pNext;
        pPrevious = pTail;

        head = pTail->next;
    }

    pRetVal = pHair->next;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
        int k;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5, 2}, {{1, 2, 3, 4, 5}, 5, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,3,4,5], k = 2
     *  Output: [2,1,4,3,5]
     *
     *  Input: head = [1,2,3,4,5], k = 3
     *  Output: [3,2,1,4,5]
     */

    struct ListNode* pHead = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        for (j = 0; j < testCase[i].nodeSize; ++j) {
            pHead = addValueToEndListNode(pHead, testCase[i].node[j]);
        }
        printf("Input: head = [");
        printList(pHead);
        printf("], k = %d\n", testCase[i].k);

        pHead = reverseKGroup(pHead, testCase[i].k);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
