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
struct ListNode* doubleIt(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    int doubleValue;
    struct ListNode* pPrevious = NULL;
    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        doubleValue = pCurrent->val * 2;
        if (doubleValue < 10) {
            pCurrent->val = doubleValue;
        } else if (pPrevious != NULL) {
            pCurrent->val = doubleValue % 10;
            pPrevious->val += 1;
        } else {
            head = (struct ListNode*)malloc(sizeof(struct ListNode));
            if (head == NULL) {
                perror("malloc");
                return pRetVal;
            }
            head->val = 1;
            head->next = pCurrent;
            pCurrent->val = doubleValue % 10;
        }
        pPrevious = pCurrent;
        pCurrent = pCurrent->next;
    }
    pRetVal = head;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 8, 9}, 3}, {{9, 9, 9}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,8,9]
     *  Output: [3,7,8]
     *
     *  Input: head = [9,9,9]
     *  Output: [1,9,9,8]
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

        pHead = doubleIt(pHead);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
