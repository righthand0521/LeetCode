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
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    if (pRetVal == NULL) {
        return pRetVal;
    }

    struct ListNode* pPrevious = NULL;
    struct ListNode* pNext = pRetVal->next;
    while (pNext != NULL) {
        pPrevious = pRetVal;
        pRetVal = pNext;
        pNext = pNext->next;
        pRetVal->next = pPrevious;
    }
    head->next = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5}, {{1, 2}, 2}, {{}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,3,4,5]
     *  Output: [5,4,3,2,1]
     *
     *  Input: head = [1,2]
     *  Output: [2,1]
     *
     *  Input: head = []
     *  Output: []
     */

    struct ListNode* pHead = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        for (j = 0; j < testCase[i].nodeSize; ++j) {
            pHead = addValueToEndListNode(pHead, testCase[i].node[j]);
        }
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pHead = reverseList(pHead);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
