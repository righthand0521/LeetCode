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
struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    if ((pRetVal == NULL) || (pRetVal->next == NULL)) {
        return pRetVal;
    }

    pRetVal = head->next;
    struct ListNode* p1 = head;
    struct ListNode* p2 = head->next;
    struct ListNode* pPrevious = NULL;
    while (p2 != NULL) {
        if (pPrevious != NULL) {
            pPrevious->next = p2;
        }
        p1->next = p2->next;
        p2->next = p1;

        pPrevious = p1;
        p1 = p1->next;
        if (p1 == NULL) {
            break;
        }
        p2 = p1->next;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 2, 3, 4}, 4}, {{}, 0}, {{1}, 1}, {{1, 2, 3, 4, 5}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,3,4]
     *  Output: [2,1,4,3]
     *
     *  Input: head = []
     *  Output: []
     *
     *  Input: head = [1]
     *  Output: [1]
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

        pHead = swapPairs(pHead);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
