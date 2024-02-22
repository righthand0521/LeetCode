#include <stdbool.h>
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
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode* pRetVal = NULL;

    pRetVal = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pRetVal == NULL) {
        perror("malloc");
        pRetVal = head;
        return pRetVal;
    }
    pRetVal->next = head;

    bool duplicate;
    int duplicateVal;
    struct ListNode* pFree = NULL;
    struct ListNode* pPrevious = pRetVal;
    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        duplicate = false;
        if ((pCurrent != NULL) && (pCurrent->next != NULL)) {
            if (pCurrent->next->val == pCurrent->val) {
                duplicate = true;
            }
        }

        if (duplicate == true) {
            duplicateVal = pCurrent->val;
            while ((pCurrent != NULL) && (pCurrent->val == duplicateVal)) {
                pFree = pCurrent;
                pCurrent = pCurrent->next;
                free(pFree);
                pFree = NULL;
            }
            pPrevious->next = pCurrent;
        } else {
            pPrevious = pCurrent;
            if (pCurrent != NULL) {
                pCurrent = pCurrent->next;
            }
        }
    }
    pFree = pRetVal;
    pRetVal = pRetVal->next;
    free(pFree);
    pFree = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 2, 3, 3, 4, 4, 5}, 7}, {{1, 1, 1, 2, 3}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,3,3,4,4,5]
     *  Output: [1,2,5]
     *
     *  Input: head = [1,1,1,2,3]
     *  Output: [2,3]
     */

    struct ListNode* pHead = NULL;
    struct ListNode* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pAnswer = deleteDuplicates(pHead);
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
