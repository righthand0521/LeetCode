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
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* pRetVal = NULL;

    // The number of nodes in each linked list is in the range[1, 100].
#define MAX_NODES (100)

    //
    int Stack1[MAX_NODES];
    memset(Stack1, 0, sizeof(Stack1));
    int idx1 = 0;
    pRetVal = l1;
    while (pRetVal != NULL) {
        Stack1[idx1++] = pRetVal->val;
        pRetVal = pRetVal->next;
    }

    int Stack2[MAX_NODES];
    memset(Stack2, 0, sizeof(Stack2));
    int idx2 = 0;
    pRetVal = l2;
    while (pRetVal != NULL) {
        Stack2[idx2++] = pRetVal->val;
        pRetVal = pRetVal->next;
    }

    //
    struct ListNode* pNew = NULL;
    int sum;
    int carry = 0;

    while ((idx1 > 0) && (idx2 > 0)) {
        sum = Stack1[--idx1] + Stack2[--idx2] + carry;

        pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pNew == NULL) {
            return pRetVal;
        }
        pNew->val = sum % 10;
        pNew->next = pRetVal;
        carry = sum / 10;
        pRetVal = pNew;
    }

    while (idx1 > 0) {
        sum = Stack1[--idx1] + carry;

        pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pNew == NULL) {
            return pRetVal;
        }
        pNew->val = sum % 10;
        pNew->next = pRetVal;
        carry = sum / 10;
        pRetVal = pNew;
    }

    while (idx2 > 0) {
        sum = Stack2[--idx2] + carry;

        pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pNew == NULL) {
            return pRetVal;
        }
        pNew->val = sum % 10;
        pNew->next = pRetVal;
        carry = sum / 10;
        pRetVal = pNew;
    }

    if (carry == 1) {
        pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pNew == NULL) {
            return pRetVal;
        }
        pNew->val = carry;
        pNew->next = pRetVal;
        pRetVal = pNew;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int l1[MAX_SIZE];
        int l1Size;
        int l2[MAX_SIZE];
        int l2Size;
    } testCase[] = {{{7, 2, 4, 3}, 4, {5, 6, 4}, 3}, {{2, 4, 3}, 3, {5, 6, 4}, 3}, {{0}, 1, {0}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: l1 = [7,2,4,3], l2 = [5,6,4]
     *  Output: [7,8,0,7]
     *
     *  Input: l1 = [2,4,3], l2 = [5,6,4]
     *  Output: [8,0,7]
     *
     *  Input: l1 = [0], l2 = [0]
     *  Output: [0]
     */

    struct ListNode* pHead1 = NULL;
    struct ListNode* pHead2 = NULL;
    struct ListNode* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead1 = buildList(testCase[i].l1, testCase[i].l1Size);
        pHead2 = buildList(testCase[i].l2, testCase[i].l2Size);
        printf("Input: ");
        printf("l1 = [");
        printList(pHead1);
        printf("], l2 = [");
        printList(pHead2);
        printf("]\n");

        pAnswer = addTwoNumbers(pHead1, pHead2);
        printf("Output: [");
        printList(pAnswer);
        printf("]\n");

        printf("\n");

        freeListNode(pHead1);
        pHead1 = NULL;
        freeListNode(pHead2);
        pHead2 = NULL;
        freeListNode(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
