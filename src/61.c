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
struct ListNode* rotateRight(struct ListNode* head, int k) {
    struct ListNode* pRetVal = head;

    if ((pRetVal == NULL) || (pRetVal->next == NULL)) {
        return pRetVal;
    }

    struct ListNode* pCurrent = head;
    int headSize = 0;
    while (pCurrent->next != NULL) {
        ++headSize;
        pCurrent = pCurrent->next;
    }
    k = headSize - (k % (headSize + 1));

    pCurrent->next = head;
    while (k--) {
        head = head->next;
    }
    pCurrent = head;
    head = head->next;
    pCurrent->next = NULL;
    pRetVal = head;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
        int k;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5, 2}, {{0, 1, 2}, 3, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,3,4,5], k = 2
     *  Output: [4,5,1,2,3]
     *
     *  Input: head = [0,1,2], k = 4
     *  Output: [2,0,1]
     */

    struct ListNode* pHead = NULL;
    struct ListNode* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("], k = %d\n", testCase[i].k);

        pAnswer = rotateRight(pHead, testCase[i].k);
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
