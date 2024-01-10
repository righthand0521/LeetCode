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

    pRetVal = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = 0;
    pRetVal->next = NULL;

    struct ListNode* pCurrent = pRetVal;
    int sum;
    int carry = 0;
    while ((l1 != NULL) || (l2 != NULL)) {
        sum = 0;

        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }

        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }

        sum += carry;
        carry = 0;
        if (sum >= 10) {
            sum %= 10;
            carry = 1;
        }

        pCurrent->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pCurrent->next == NULL) {
            perror("malloc");
            return pRetVal;
        }
        pCurrent->next->val = sum;
        pCurrent->next->next = NULL;
        pCurrent = pCurrent->next;
    }

    if (carry == 1) {
        pCurrent->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pCurrent->next == NULL) {
            perror("malloc");
            return pRetVal;
        }
        pCurrent->next->val = carry;
        pCurrent->next->next = NULL;
    }

    pCurrent = pRetVal;
    pRetVal = pRetVal->next;
    free(pCurrent);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int l1[MAX_SIZE];
        int l1Size;
        int l2[MAX_SIZE];
        int l2Size;
    } testCase[] = {{{2, 4, 3}, 3, {5, 6, 4}, 3},
                    {{0}, 1, {0}, 1},
                    {{9, 9, 9, 9, 9, 9, 9}, 7, {9, 9, 9, 9}, 4},
                    {{7, 1, 6}, 3, {5, 9, 2}, 3},
                    {{9, 7, 8}, 3, {6, 8, 5}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: l1 = [2,4,3], l2 = [5,6,4]
     *  Output: [7,0,8]
     *
     *  Input: l1 = [0], l2 = [0]
     *  Output: [0]
     *
     *  Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
     *  Output: [8,9,9,9,0,0,0,1]
     *
     *  Input: l1 = [7,1,6], l2 = [5,9,2]
     *  Output: [2,1,9]
     *
     *  Input: l1 = [9,7,8], l2 = [6,8,5]
     *  Output: [5,6,4,1]
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
