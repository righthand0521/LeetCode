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
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* pRetVal = head;

    struct ListNode* pRemove = head;
    struct ListNode* pCurrent = head;
    for (int i = 0; i < n; ++i) {
        if (pCurrent == NULL) {
            break;
        }
        pCurrent = pCurrent->next;
    }
    if (pCurrent == NULL) {
        pRetVal = pRemove->next;
        free(pRemove);
        pRemove = NULL;
        return pRetVal;
    }

    while (pCurrent->next != NULL) {
        pRemove = pRemove->next;
        pCurrent = pCurrent->next;
    }
    pCurrent = pRemove;
    pRemove = pRemove->next;
    pCurrent->next = pRemove->next;
    free(pRemove);
    pRemove = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (30)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
        int n;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5, 2}, {{1}, 1, 1}, {{1, 2}, 2, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,3,4,5], n = 2
     *  Output: [1,2,3,5]
     *
     *  Input: head = [1], n = 1
     *  Output: []
     *
     *  Input: head = [1,2], n = 1
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
        printf("], n = %d\n", testCase[i].n);

        pHead = removeNthFromEnd(pHead, testCase[i].n);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
