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
struct ListNode* middleNode(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    if ((head == NULL) || (head->next == NULL)) {
        return pRetVal;
    }

    struct ListNode* pOne = head;
    struct ListNode* pTwo = head;
    while ((pTwo != NULL) && (pTwo->next != NULL)) {
        pOne = pOne->next;
        pTwo = pTwo->next;
        if (pTwo != NULL) {
            pTwo = pTwo->next;
        }
    }
    pRetVal = pOne;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5}, {{1, 2, 3, 4, 5, 6}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,3,4,5]
     *  Output: [3,4,5]
     *
     *  Input: head = [1,2,3,4,5,6]
     *  Output: [4,5,6]
     */

    struct ListNode* pHead = NULL;
    struct ListNode* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: ");
        for (j = 0; j < testCase[i].nodeSize; ++j) {
            pHead = addValueToEndListNode(pHead, testCase[i].node[j]);
        }
        printf("head = [");
        printList(pHead);
        printf("]\n");

        pAnswer = middleNode(pHead);
        printf("Output: [");
        printList(pAnswer);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
