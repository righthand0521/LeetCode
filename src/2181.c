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
struct ListNode* mergeNodes(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    int sum = 0;
    struct ListNode* pFree = NULL;
    struct ListNode* pPrevious = head;
    struct ListNode* pCurrent = head->next;
    while (pCurrent != NULL) {
        if (pCurrent->val != 0) {
            sum += pCurrent->val;
            pPrevious->next = pCurrent->next;
            pFree = pCurrent;
            free(pFree);
            pFree = NULL;
        } else {
            pCurrent->val = sum;
            sum = 0;
            pPrevious = pCurrent;
        }

        pCurrent = pPrevious->next;
    }
    pRetVal = head->next;
    pFree = head;
    free(pFree);
    pFree = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{0, 3, 1, 0, 4, 5, 2, 0}, 8}, {{0, 1, 0, 3, 0, 2, 2, 0}, 8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [0,3,1,0,4,5,2,0]
     *  Output: [4,11]
     *
     *  Input: head = [0,1,0,3,0,2,2,0]
     *  Output: [1,3,4]
     */

    struct ListNode* pHead = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].nums, testCase[i].numsSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pHead = mergeNodes(pHead);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
