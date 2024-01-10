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
struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2) {
    struct ListNode *pRetVal = NULL;

    struct ListNode *p1 = list1;
    struct ListNode *p2 = list2;
    struct ListNode *pNew = NULL;
    struct ListNode *pCurrent = NULL;
    while ((p1 != NULL) || (p2 != NULL)) {
        pNew = (struct ListNode *)malloc(sizeof(struct ListNode));
        if (pNew == NULL) {
            perror("malloc");
            return NULL;
        }

        if (p1 == NULL) {
            pNew->val = p2->val;
            p2 = p2->next;
        } else if (p2 == NULL) {
            pNew->val = p1->val;
            p1 = p1->next;
        } else {
            if (p1->val <= p2->val) {
                pNew->val = p1->val;
                p1 = p1->next;
            } else {
                pNew->val = p2->val;
                p2 = p2->next;
            }
        }

        if (pRetVal == NULL) {
            pRetVal = pNew;
            pRetVal->next = NULL;
            pCurrent = pRetVal;
        } else {
            pCurrent->next = pNew;
            pCurrent = pNew;
            pCurrent->next = NULL;
        }

        pNew = NULL;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int nums1[MAX_SIZE];
        int nums1Size;
        int nums2[MAX_SIZE];
        int nums2Size;
    } testCase[] = {{{1, 2, 4}, 3, {1, 3, 4}, 3}, {{}, 0, {}, 0}, {{}, 0, {0}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: list1 = [1,2,4], list2 = [1,3,4]
     *  Output: [1,1,2,3,4,4]
     *
     *  Input: list1 = [], list2 = []
     *  Output: []
     *
     *  Input: list1 = [], list2 = [0]
     *  Output: [0]
     */

    struct ListNode *pAnswer = NULL;
    struct ListNode *pHead1 = NULL;
    struct ListNode *pHead2 = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead1 = buildList(testCase[i].nums1, testCase[i].nums1Size);
        pHead2 = buildList(testCase[i].nums2, testCase[i].nums2Size);
        printf("Input: list1 = [");
        printList(pHead1);
        printf("], list2 = [");
        printList(pHead2);
        printf("]\n");

        pAnswer = mergeTwoLists(pHead1, pHead2);
        printf("Output: [");
        printList(pAnswer);
        printf("]\n");

        printf("\n");

        freeListNode(pAnswer);
        pAnswer = NULL;
        freeListNode(pHead1);
        pHead1 = NULL;
        freeListNode(pHead2);
        pHead2 = NULL;
    }

    return EXIT_SUCCESS;
}
