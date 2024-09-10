#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int gcd(int a, int b) {
    int retVal = 1;

    int tmp;
    while (b != 0) {
        tmp = a;
        a = b;
        b = tmp % b;
    }
    retVal = a;

    return retVal;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* insertGreatestCommonDivisors(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    if ((pRetVal == NULL) || (pRetVal->next == NULL)) {
        return pRetVal;
    }

    int gcdValue;
    struct ListNode* pGcdNode;
    struct ListNode* pNode1 = pRetVal;
    struct ListNode* pNode2 = pRetVal->next;
    while (pNode2 != NULL) {
        gcdValue = gcd(pNode1->val, pNode2->val);

        pGcdNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pGcdNode == NULL) {
            perror("malloc");
            return pRetVal;
        }
        pGcdNode->val = gcdValue;
        pGcdNode->next = NULL;
        pNode1->next = pGcdNode;
        pGcdNode->next = pNode2;

        pNode1 = pNode2;
        pNode2 = pNode2->next;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_NODES (5000)
    struct testCaseType {
        int node[MAX_NODES];
        int nodeSize;
    } testCase[] = {{{18, 6, 10, 3}, 4}, {{7}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [18,6,10,3]
     *  Output: [18,6,6,2,10,1,3]
     *
     *  Input: head = [7]
     *  Output: [7]
     */

    struct ListNode* pHead = NULL;
    struct ListNode* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pAnswer = insertGreatestCommonDivisors(pHead);
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
