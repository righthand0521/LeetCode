#include <math.h>
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
int pairSum(struct ListNode* head) {
    int retVal = 0;

    struct ListNode* pReverse = NULL;
    int pReverseCount = 0;
    struct ListNode* pNew = NULL;
    struct ListNode* pFree = NULL;

    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pNew == NULL) {
            perror("malloc");
            pCurrent = pReverse;
            while (pCurrent != NULL) {
                pFree = pCurrent;
                pCurrent = pCurrent->next;
                free(pFree);
            }
            return retVal;
        }
        pNew->val = pCurrent->val;
        pNew->next = pReverse;
        pReverse = pNew;
        ++pReverseCount;

        pCurrent = pCurrent->next;
    }

    struct ListNode* p1 = head;
    struct ListNode* p2 = pReverse;
    int i;
    for (i = 0; i < pReverseCount / 2; ++i) {
        retVal = fmax(retVal, p1->val + p2->val);

        p1 = p1->next;
        p2 = p2->next;
    }

    pCurrent = pReverse;
    while (pCurrent != NULL) {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        free(pFree);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{5, 4, 2, 1}, 4}, {{4, 2, 2, 3}, 4}, {{1, 100000}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [5,4,2,1]
     *  Output: 6
     *
     *  Input: head = [4,2,2,3]
     *  Output: 7
     *
     *  Input: head = [1,100000]
     *  Output: 100001
     */

    struct ListNode* pHead = NULL;
    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        answer = pairSum(pHead);
        printf("Output: %d\n", answer);

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
