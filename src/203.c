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
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode* pRetVal = head;

    if (pRetVal == NULL) {
        return pRetVal;
    }

    struct ListNode* pPrevious = NULL;
    struct ListNode* pFree = head;
    while (pFree != NULL) {
        if (pFree->val != val) {
            pPrevious = pFree;
            pFree = pFree->next;
            continue;
        }

        if (pPrevious != NULL) {
            pPrevious->next = pFree->next;
            free(pFree);
            pFree = pPrevious->next;
        } else {
            pRetVal = pRetVal->next;
            free(pFree);
            pFree = pRetVal;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
        int val;
    } testCase[] = {{{1, 2, 6, 3, 4, 5, 6}, 7, 6}, {{}, 0, 1}, {{7, 7, 7, 7}, 4, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,6,3,4,5,6], val = 6
     *  Output: [1,2,3,4,5]
     *
     *  Input: head = [], val = 1
     *  Output: []
     *
     *  Input: head = [7,7,7,7], val = 7
     *  Output: []
     */

    struct ListNode* pHead = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("], val = %d\n", testCase[i].val);

        pHead = removeElements(pHead, testCase[i].val);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
