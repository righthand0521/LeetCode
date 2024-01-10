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
struct ListNode* reverseEvenLengthGroups(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    int i;
    int count = 0;
    int length = 0;
    struct ListNode* pTmp = NULL;
    struct ListNode* pNext = NULL;
    struct ListNode* pPrevious = NULL;
    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        ++count;
        length = 0;
        pNext = pCurrent;
        while ((length < count) && (pNext != NULL)) {
            ++length;
            pNext = pNext->next;
        }

        if (length % 2 == 0) {
            for (i = 0; i < (length - 1); ++i) {
                pTmp = pCurrent->next;
                pCurrent->next = pCurrent->next->next;
                pTmp->next = pPrevious->next;
                pPrevious->next = pTmp;
            }
        } else {
            for (i = 0; i < (length - 1); ++i) {
                pPrevious = pCurrent;
                pCurrent = pCurrent->next;
            }
        }

        pPrevious = pCurrent;
        pCurrent = pCurrent->next;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_NODES (int)(1e5)
    struct testCaseType {
        int node[MAX_NODES];
        int nodeSize;
    } testCase[] = {{{5, 2, 6, 3, 9, 1, 7, 3, 8, 4}, 10}, {{1, 1, 0, 6}, 4}, {{1, 1, 0, 6, 5}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [5,2,6,3,9,1,7,3,8,4]
     *  Output: [5,6,2,3,9,1,4,8,3,7]
     *
     *  Input: head = [1,1,0,6]
     *  Output: [1,0,1,6]
     *
     *  Input: head = [1,1,0,6,5]
     *  Output: [1,0,1,5,6]
     */

    struct ListNode* pHead = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pHead = reverseEvenLengthGroups(pHead);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
