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
bool isPalindrome(struct ListNode* head) {
    bool retVal = true;

    //
    struct ListNode* pCurrent = head;
    if ((pCurrent == NULL) || (pCurrent->next == NULL)) {
        return retVal;
    }

    // stack push
    struct ListNode* pStackTop = NULL;
    struct ListNode* pNew = NULL;
    while (pCurrent != NULL) {
        pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
        if (pNew == NULL) {
            perror("malloc");
            goto exit;
        }
        pNew->val = pCurrent->val;
        pNew->next = pStackTop;
        pStackTop = pNew;

        pCurrent = pCurrent->next;
    }

    // stack pop
    pCurrent = head;
    int popValue;
    struct ListNode* pFree = NULL;
    while (pCurrent != NULL) {
        pFree = pStackTop;
        popValue = pFree->val;
        pStackTop = pStackTop->next;
        free(pFree);
        pFree = NULL;
        if (pCurrent->val != popValue) {
            retVal = false;
            break;
        }
        pCurrent = pCurrent->next;
    }

    // free
exit:
    while (pStackTop != NULL) {
        pFree = pStackTop;
        pStackTop = pStackTop->next;
        free(pFree);
        pFree = NULL;
    }
    pStackTop = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 2, 2, 1}, 4}, {{1, 2}, 2}, {{1, 2, 1}, 3}, {{1, 2, 3}, 3}, {{1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,2,1]
     *  Output: true
     *
     *  Input: head = [1,2]
     *  Output: false
     */

    struct ListNode* pHead = NULL;
    bool answer = true;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        for (j = 0; j < testCase[i].nodeSize; ++j) {
            pHead = addValueToEndListNode(pHead, testCase[i].node[j]);
        }
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        answer = isPalindrome(pHead);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
