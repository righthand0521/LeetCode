#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* pRetVal = NULL;

    struct ListNode* pPrevious = NULL;
    struct ListNode* pCurrent = head;
    struct ListNode* pNext = NULL;
    while (pCurrent != NULL) {
        pNext = pCurrent->next;
        pCurrent->next = pPrevious;
        pPrevious = pCurrent;
        pCurrent = pNext;
    }
    pRetVal = pPrevious;

    return pRetVal;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNodes(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    head = reverseList(head);

    struct ListNode* pDeleted = NULL;
    int maximum = 0;
    struct ListNode* pPrevious = NULL;
    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        maximum = fmax(maximum, pCurrent->val);
        if (pCurrent->val >= maximum) {
            pPrevious = pCurrent;
            pCurrent = pCurrent->next;
            continue;
        }

        if (pPrevious != NULL) {
            pPrevious->next = pCurrent->next;
        } else {
            head = pCurrent->next;
        }

        pDeleted = pCurrent;
        pCurrent = pCurrent->next;
        free(pDeleted);
        pDeleted = NULL;
    }

    pRetVal = reverseList(head);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{5, 2, 13, 3, 8}, 5}, {{1, 1, 1, 1}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [5,2,13,3,8]
     *  Output: [13,8]
     *
     *  Input: head = [1,1,1,1]
     *  Output: [1,1,1,1]
     */

    struct ListNode* pHead = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: ");
        for (j = 0; j < testCase[i].nodeSize; ++j) {
            pHead = addValueToEndListNode(pHead, testCase[i].node[j]);
        }
        printf("head = [");
        printList(pHead);
        printf("]\n");

        pHead = removeNodes(pHead);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
