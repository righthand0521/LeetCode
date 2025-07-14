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
int getDecimalValue(struct ListNode* head) {
    int retVal = head->val;

    struct ListNode* pCurrent = head->next;
    while (pCurrent != NULL) {
        retVal = (retVal << 1) | pCurrent->val;
        pCurrent = pCurrent->next;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (30)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 0, 1}, 3}, {{0}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,0,1]
     *  Output: 5
     *
     *  Input: head = [0]
     *  Output: 0
     */

    struct ListNode* pHead = NULL;
    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        answer = getDecimalValue(pHead);
        printf("Output: %d\n", answer);

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}