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
struct ListNode* deleteMiddle(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    // The number of nodes is 1
    if (pRetVal->next == NULL) {
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    // Middle of the Linked List: https://leetcode.com/problems/middle-of-the-linked-list/
    struct ListNode* pOne = pRetVal;
    struct ListNode* pTwo = pRetVal;
    while ((pTwo != NULL) && (pTwo->next != NULL)) {
        pOne = pOne->next;
        pTwo = pTwo->next;
        if (pTwo != NULL) {
            pTwo = pTwo->next;
        }
    }

    // The number of nodes is 2
    if (pOne->next == NULL) {
        pRetVal->next = NULL;
        free(pOne);
        pOne = NULL;
        return pRetVal;
    }

    // Delete Node in a Linked List: https://leetcode.com/problems/delete-node-in-a-linked-list/
    struct ListNode* pFree = pOne->next;
    *pOne = *pOne->next;
    free(pFree);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 3, 4, 7, 1, 2, 6}, 7}, {{1, 2, 3, 4}, 4}, {{2, 1}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,3,4,7,1,2,6]
     *  Output: [1,3,4,1,2,6]
     *
     *  Input: head = [1,2,3,4]
     *  Output: [1,2,4]
     *
     *  Input: head = [2,1]
     *  Output: [2]
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

        pHead = deleteMiddle(pHead);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
