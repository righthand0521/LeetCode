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
struct ListNode* swapNodes(struct ListNode* head, int k) {
    struct ListNode* pRetVal = head;

    struct ListNode* pCurrent = head;
    struct ListNode* pSwapHead = NULL;
    struct ListNode* pSwapTail = NULL;

    int idx = 0;
    while (pCurrent != NULL) {
        ++idx;
        if (idx >= k) {
            break;
        }

        pCurrent = pCurrent->next;
    }
    pSwapHead = pCurrent;

    pCurrent = pCurrent->next;
    pSwapTail = head;
    while (pCurrent != NULL) {
        pCurrent = pCurrent->next;
        pSwapTail = pSwapTail->next;
    }

    int tmp = pSwapHead->val;
    pSwapHead->val = pSwapTail->val;
    pSwapTail->val = tmp;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
        int k;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5, 2}, {{7, 9, 6, 6, 7, 8, 3, 0, 9, 5}, 10, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,3,4,5], k = 2
     *  Output: [1,4,3,2,5]
     *
     *  Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
     *  Output: [7,9,6,6,8,7,3,0,9,5]
     */

    struct ListNode* pHead = NULL;
    struct ListNode* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("], k = %d\n", testCase[i].k);

        pAnswer = swapNodes(pHead, testCase[i].k);
        printf("Output: [");
        printList(pAnswer);
        printf("]\n");

        printf("\n");

        freeListNode(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
