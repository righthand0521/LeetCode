#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define ARRAY (0)
#define STACK (1)
#define REVERSE (1)
#if (ARRAY)
#elif (STACK)
#define EMPTY_STACK_POP (-1)  // 0 <= Node.val <= 9
struct ListNode* stackPush(struct ListNode* pTop, int value) {
    struct ListNode* pRetVal = pTop;

    struct ListNode* pNew = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    if (pNew == NULL) {
        perror("pNew");
        return pRetVal;
    }
    pNew->val = value;
    pNew->next = NULL;

    if (pRetVal != NULL) {
        pNew->next = pRetVal;
    }
    pRetVal = pNew;

    return pRetVal;
}
int stackPop(struct ListNode** pTop) {
    int retVal = EMPTY_STACK_POP;

    struct ListNode* pCurrent = (*pTop);
    if (pCurrent == NULL) {
        printf("Stack is Empty");
        return retVal;
    }
    retVal = pCurrent->val;
    (*pTop) = pCurrent->next;
    free(pCurrent);

    return retVal;
}
void stackFree(struct ListNode* pTop) {
    struct ListNode* pFree = NULL;
    while (pTop != NULL) {
        pFree = pTop;
        pTop = pTop->next;
        free(pFree);
    }
}
#elif (REVERSE)
#endif
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool isPalindrome(struct ListNode* head) {
    bool retVal = true;

    struct ListNode* pCurrent = head;
    if ((pCurrent == NULL) || (pCurrent->next == NULL)) {
        return retVal;
    }

#if (ARRAY)
    printf("ARRAY\n");

#define MAX_NODES (100000)
    int TwoPointers[MAX_NODES];
    memset(TwoPointers, 0, sizeof(TwoPointers));

    int count = 0;
    while (pCurrent != NULL) {
        TwoPointers[count++] = pCurrent->val;
        pCurrent = pCurrent->next;
    }

    int left = 0;
    int right = count - 1;
    while (left < right) {
        if (TwoPointers[left++] != TwoPointers[right--]) {
            retVal = false;
            break;
        }
    }
#elif (STACK)
    printf("STACK\n");

    struct ListNode* pStackTop = NULL;
    while (pCurrent != NULL) {
        pStackTop = stackPush(pStackTop, pCurrent->val);
        pCurrent = pCurrent->next;
    }

    pCurrent = head;
    while (pCurrent != NULL) {
        if (pCurrent->val != stackPop(&pStackTop)) {
            retVal = false;
            break;
        }
        pCurrent = pCurrent->next;
    }
    stackFree(pStackTop);
    pStackTop = NULL;

#elif (REVERSE)
    printf("REVERSE\n");

    struct ListNode* pReverseHead = NULL;
    struct ListNode* pNext = NULL;
    struct ListNode* pNextNext = pCurrent;
    while ((pNextNext != NULL) && (pNextNext->next != NULL)) {
        pNextNext = pNextNext->next->next;

        pNext = pCurrent->next;
        pCurrent->next = pReverseHead;
        pReverseHead = pCurrent;
        pCurrent = pNext;
    }

    while (pCurrent != NULL) {
        if (pCurrent->val != pReverseHead->val) {
            pCurrent = pCurrent->next;
            continue;
        }
        pCurrent = pCurrent->next;
        pReverseHead = pReverseHead->next;
    }
    if (pReverseHead != NULL) {
        retVal = false;
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
#define MAX_SIZE (int)(1e5)
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
