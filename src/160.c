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
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
    struct ListNode* pRetVal = NULL;

    int lenA = 0;
    struct ListNode* pCurrentA = headA;
    while (pCurrentA->next != NULL) {
        lenA++;
        pCurrentA = pCurrentA->next;
    }

    int lenB = 0;
    struct ListNode* pCurrentB = headB;
    while (pCurrentB->next != NULL) {
        lenB++;
        pCurrentB = pCurrentB->next;
    }

    if (pCurrentA != pCurrentB) {
        return pRetVal;
    }

    int diff = (lenA > lenB) ? lenA - lenB : lenB - lenA;

    pRetVal = (lenA > lenB) ? headA : headB;
    int i;
    for (i = 0; i < diff; ++i) {
        pRetVal = pRetVal->next;
    }

    pCurrentA = (lenA > lenB) ? pRetVal : headA;
    pCurrentB = (lenA > lenB) ? headB : pRetVal;
    while (pRetVal != NULL) {
        if (pCurrentA == pCurrentB) {
            return pRetVal;
        }
        pRetVal = pRetVal->next;
        pCurrentA = pCurrentA->next;
        pCurrentB = pCurrentB->next;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_NODES (3 * 10000)
    struct testCaseType {
        int intersectVal;
        int nodeA[MAX_NODES];
        int nodeSizeA;
        int nodeB[MAX_NODES];
        int nodeSizeB;
        int skipA;
        int skipB;
    } testCase[] = {{8, {4, 1, 8, 4, 5}, 5, {5, 6, 1, 8, 4, 5}, 6, 2, 3},
                    {2, {1, 9, 1, 2, 4}, 5, {3, 2, 4}, 3, 3, 1},
                    {0, {2, 6, 4}, 3, {1, 5}, 2, 3, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
     *  Output: Intersected at '8'
     *
     *  Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
     *  Output: Intersected at '2'
     *
     *  Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
     *  Output: No intersection
     */

    struct ListNode* pIntersect = NULL;
    struct ListNode* pHeadA = NULL;
    struct ListNode* pHeadB = NULL;
    struct ListNode* pAnswer = NULL;
    struct ListNode* pFree = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: intersectVal = %d, ", testCase[i].intersectVal);
        for (j = testCase[i].skipA; j < testCase[i].nodeSizeA; ++j) {
            pIntersect = addValueToEndListNode(pIntersect, testCase[i].nodeA[j]);
        }
        for (j = 0; j < testCase[i].skipA; ++j) {
            pHeadA = addValueToEndListNode(pHeadA, testCase[i].nodeA[j]);
        }
        pHeadA = mergeListNode(pHeadA, pIntersect);
        printf("listA = [");
        printList(pHeadA);
        printf("], ");
        for (j = 0; j < testCase[i].skipB; ++j) {
            pHeadB = addValueToEndListNode(pHeadB, testCase[i].nodeB[j]);
        }
        pHeadB = mergeListNode(pHeadB, pIntersect);
        printf("listB = [");
        printList(pHeadB);
        printf("], ");
        printf("skipA = %d, ", testCase[i].skipA);
        printf("skipB = %d\n", testCase[i].skipB);

        printf("Output: ");
        pAnswer = getIntersectionNode(pHeadA, pHeadB);
        if (pAnswer == NULL) {
            printf("No intersection\n");
        } else {
            printf("Intersected at '%d'\n", pAnswer->val);
        }

        printf("\n");

        pFree = pHeadA;
        for (j = 1; j < testCase[i].skipA; ++j) {
            pFree = pFree->next;
        }
        pFree->next = NULL;
        pFree = pHeadB;
        for (j = 1; j < testCase[i].skipB; ++j) {
            pFree = pFree->next;
        }
        pFree->next = NULL;
        freeListNode(pIntersect);
        pIntersect = NULL;
        freeListNode(pHeadA);
        pHeadA = NULL;
        freeListNode(pHeadB);
        pHeadB = NULL;
    }

    return EXIT_SUCCESS;
}
