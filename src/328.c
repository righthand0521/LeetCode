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
struct ListNode* oddEvenList(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    if (head == NULL) {
        return pRetVal;
    }

    struct ListNode* pOdd = pRetVal;
    struct ListNode* pEven = pRetVal->next;
    struct ListNode* pEvenHead = pRetVal->next;
    while ((pEven != NULL) && (pEven->next != NULL)) {
        pOdd->next = pOdd->next->next;
        pEven->next = pEven->next->next;
        pOdd = pOdd->next;
        pEven = pEven->next;
    }
    pOdd->next = pEvenHead;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5}, {{2, 1, 3, 5, 6, 4, 7}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,3,4,5]
     *  Output: [1,3,5,2,4]
     *
     *  Input: head = [2,1,3,5,6,4,7]
     *  Output: [2,3,6,7,1,5,4]
     */

    struct ListNode* pHead = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pHead = oddEvenList(pHead);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
