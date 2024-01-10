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
struct ListNode* detectCycle(struct ListNode* head) {
    struct ListNode* pRetVal = NULL;

    if (head == NULL) {
        return pRetVal;
    }

    struct ListNode* pOne = head;
    struct ListNode* pTwo = head;
    while ((pOne->next != NULL) && (pTwo->next != NULL) && (pTwo->next->next != NULL)) {
        pOne = pOne->next;
        pTwo = pTwo->next->next;
        if (pOne == pTwo) {
            pRetVal = head;
            break;
        }
    }
    if (pRetVal != head) {
        return pRetVal;
    }

    while (pRetVal != pOne) {
        pRetVal = pRetVal->next;
        pOne = pOne->next;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_NODES (10000)
    struct testCaseType {
        int node[MAX_NODES];
        int nodeSize;
        int pos;
    } testCase[] = {
        {{3, 2, 0, -4}, 4, 1}, {{1, 2}, 2, 0}, {{1}, 1, LIST_VALID_CYCLE_INDEX}, {{1, 2}, 2, LIST_VALID_CYCLE_INDEX}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [3,2,0,-4], pos = 1
     *  Output: tail connects to node index 1
     *
     *  Input: head = [1,2], pos = 0
     *  Output: tail connects to node index 0
     *
     *  Input: head = [1], pos = -1
     *  Output: no cycle
     */

    struct ListNode* pHead = NULL;
    struct ListNode* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("], ");
        printf("pos = %d\n", testCase[i].pos);
        if (testCase[i].pos != LIST_VALID_CYCLE_INDEX) {
            pHead = addListNodeCycle(pHead, testCase[i].pos);
        }

        pAnswer = detectCycle(pHead);
        if (pAnswer == NULL) {
            printf("Output: no cycle\n");
        } else {
            printf("Output: tail connects to node index %d\n", testCase[i].pos);
        }

        printf("\n");

        if (testCase[i].pos != LIST_VALID_CYCLE_INDEX) {
            pHead = removeListNodeCycle(pHead, testCase[i].pos);
        }
        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
