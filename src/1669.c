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
struct ListNode* mergeInBetween(struct ListNode* list1, int a, int b, struct ListNode* list2) {
    struct ListNode* pRetVal = list1;

    int i;
    struct ListNode* pPrevious = NULL;
    struct ListNode* pNext1 = list1;
    struct ListNode* pNext2 = NULL;

    for (i = 0; i < a; ++i) {
        pPrevious = pNext1;
        pNext1 = pNext1->next;
    }
    pNext2 = pPrevious;

    for (i = a; i <= b; ++i) {
        pPrevious->next = pNext1->next;
        free(pNext1);
        pNext1 = pPrevious->next;
    }

    pNext2->next = list2;
    while (pNext2 != NULL) {
        pPrevious = pNext2;
        pNext2 = pNext2->next;
    }
    pPrevious->next = pNext1;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int list1[MAX_SIZE];
        int list1Size;
        int a;
        int b;
        int list2[MAX_SIZE];
        int list2Size;
    } testCase[] = {{{0, 1, 2, 3, 4, 5}, 6, 3, 4, {1000000, 1000001, 1000002}, 3},
                    {{0, 1, 2, 3, 4, 5, 6}, 7, 2, 5, {1000000, 1000001, 1000002, 1000003, 1000004}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: list1 = [0,1,2,3,4,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
     *  Output: [0,1,2,1000000,1000001,1000002,5]
     *
     *  Input: list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 = [1000000,1000001,1000002,1000003,1000004]
     *  Output: [0,1,1000000,1000001,1000002,1000003,1000004,6]
     */

    struct ListNode* pList1 = NULL;
    struct ListNode* pList2 = NULL;
    struct ListNode* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        for (j = 0; j < testCase[i].list1Size; ++j) {
            pList1 = addValueToEndListNode(pList1, testCase[i].list1[j]);
        }
        for (j = 0; j < testCase[i].list2Size; ++j) {
            pList2 = addValueToEndListNode(pList2, testCase[i].list2[j]);
        }
        printf("Input: list1 = [");
        printList(pList1);
        printf("], a = %d, b = %d", testCase[i].a, testCase[i].b);
        printf(", list2 = [");
        printList(pList2);
        printf("]\n");

        pAnswer = mergeInBetween(pList1, testCase[i].a, testCase[i].b, pList2);
        printf("Output: [");
        printList(pAnswer);
        printf("]\n");

        printf("\n");

        freeListNode(pList1);
        pList1 = NULL;
        pList2 = NULL;
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
