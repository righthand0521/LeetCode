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
bool hasCycle(struct ListNode* head) {
    bool retVal = false;

    if ((head == NULL) || (head->next == NULL)) {
        return retVal;
    }

    struct ListNode* pOne = head;
    struct ListNode* pTwo = head->next;
    while (pOne != pTwo) {
        if ((pTwo == NULL) || (pTwo->next == NULL)) {
            return retVal;
        }
        pOne = pOne->next;
        pTwo = pTwo->next->next;
    }
    retVal = true;

    return retVal;
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
     *  Output: true
     *
     *  Input: head = [1,2], pos = 0
     *  Output: true
     *
     *  Input: head = [1], pos = -1
     *  Output: false
     *
     *  Input: head = [1,2], pos = -1
     *  Output: false
     */

    struct ListNode* pHead = NULL;
    bool answer = true;
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

        answer = hasCycle(pHead);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        if (testCase[i].pos != LIST_VALID_CYCLE_INDEX) {
            pHead = removeListNodeCycle(pHead, testCase[i].pos);
        }
        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
