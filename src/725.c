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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct ListNode** splitListToParts(struct ListNode* head, int k, int* returnSize) {
    struct ListNode** pRetVal = NULL;

    (*returnSize) = 0;

    int nodeCount = 0;
    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        ++nodeCount;
        pCurrent = pCurrent->next;
    }
    int quotient = nodeCount / k;
    int remainder = nodeCount % k;

    pRetVal = (struct ListNode**)malloc(k * sizeof(struct ListNode*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    pCurrent = head;
    struct ListNode* pNext;
    int partsCount;
    int i, j;
    for (i = 0; i < k; ++i) {
        if (pCurrent == NULL) {
            pRetVal[i] = NULL;
            continue;
        }

        pRetVal[i] = pCurrent;
        partsCount = quotient + ((remainder > i) ? (1) : (0));
        for (j = 0; j < partsCount - 1; ++j) {
            if (pCurrent != NULL) {
                pCurrent = pCurrent->next;
            }
        }
        pNext = pCurrent->next;
        pCurrent->next = NULL;
        pCurrent = pNext;
    }
    (*returnSize) = k;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
        int k;
        int returnSize;
    } testCase[] = {{{1, 2, 3}, 3, 5, 0}, {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,3], k = 5
     *  Output: [[1],[2],[3],[],[]]
     *
     *  Input: head = [1,2,3,4,5,6,7,8,9,10], k = 3
     *  Output: [[1,2,3,4],[5,6,7],[8,9,10]]
     */

    struct ListNode** pAnswer = NULL;
    struct ListNode* pHead = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        for (j = 0; j < testCase[i].nodeSize; ++j) {
            pHead = addValueToEndListNode(pHead, testCase[i].node[j]);
        }
        printf("Input: head = [");
        printList(pHead);
        printf("], k = %d\n", testCase[i].k);

        pAnswer = splitListToParts(pHead, testCase[i].k, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            printList(pAnswer[j]);
            printf("]");

            freeListNode(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        if (testCase[i].returnSize == 0) {
            freeListNode(pHead);
        }
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
