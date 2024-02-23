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
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    if ((head == NULL) || (head->next == NULL)) {
        return pRetVal;
    }

    struct ListNode* pCurrent = head->next;
    struct ListNode* pPrevious = head;
    while (pCurrent != NULL) {
        if (pCurrent->val == pPrevious->val) {
            pPrevious->next = pCurrent->next;
            free(pCurrent);
            pCurrent = pPrevious->next;
        } else {
            pPrevious = pCurrent;
            pCurrent = pCurrent->next;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 1, 2}, 3}, {{1, 1, 2, 3, 3}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,1,2]
     *  Output: [1,2]
     *
     *  Input: head = [1,1,2,3,3]
     *  Output: [1,2,3]
     */

    struct ListNode* pHead = NULL;
    struct ListNode* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pAnswer = deleteDuplicates(pHead);
        printf("Output: [");
        printList(pAnswer);
        printf("]\n");

        printf("\n");

        freeListNode(pAnswer);
        pAnswer = NULL;
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
