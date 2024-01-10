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
struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode* pRetVal = head;

    if (head == NULL) {
        return pRetVal;
    }

    struct ListNode* pLessHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pLessHead == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pLessHead->next = NULL;
    struct ListNode* pLess = pLessHead;
    struct ListNode* pGreatHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pGreatHead == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pGreatHead->next = NULL;
    struct ListNode* pGreat = pGreatHead;

    while (pRetVal != NULL) {
        if (pRetVal->val < x) {
            pLess->next = pRetVal;
            pLess = pLess->next;
        } else {
            pGreat->next = pRetVal;
            pGreat = pGreat->next;
        }
        pRetVal = pRetVal->next;
    }
    pLess->next = pGreatHead->next;
    pGreat->next = NULL;
    pRetVal = pLessHead->next;

    free(pLessHead);
    free(pGreatHead);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_NODES (30)
    struct testCaseType {
        int node[MAX_NODES];
        int nodeSize;
        int x;
    } testCase[] = {
        {{1, 4, 3, 2, 5, 2}, 6, 3},    {{2, 1}, 2, 2}, {{}, 0, 0}, {{1}, 1, 2}, {{1, 1}, 2, 2}, {{1, 1}, 2, 0},
        {{3, 5, 8, 5, 10, 2, 1}, 7, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,4,3,2,5,2], x = 3
     *  Output: [1,2,2,4,3,5]
     *
     *  Input: head = [2,1], x = 2
     *  Output: [1,2]
     *
     *  Input: head = [], x = 0
     *  Output: []
     *
     *  Input: head = [1], x = 2
     *  Output: [1]
     *
     *  Input: head = [1,1], x = 2
     *  Output: [1,1]
     *
     *  Input: head = [1,1], x = 0
     *  Output: [1,1]
     *
     *  Input: head = [3,5,8,5,10,2,1], x = 5
     *  Output: [3,2,1,5,8,5,10]
     */

    struct ListNode* pHead = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("], x = %d\n", testCase[i].x);

        pHead = partition(pHead, testCase[i].x);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
