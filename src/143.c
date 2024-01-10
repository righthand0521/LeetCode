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
void reorderList(struct ListNode* head) {
    if (head == NULL) {
        return;
    }

    // The number of nodes in the list is in the range [1, 5 * 10^4].
#define MAX_NODEADDRESS (int)((5) * (1e4))
    struct ListNode* nodeAddress[MAX_NODEADDRESS];

    int nodeCount = 0;
    struct ListNode* pNext = head;
    while (pNext != NULL) {
        nodeAddress[nodeCount++] = pNext;
        pNext = pNext->next;
    }

    int left = 0;
    int right = nodeCount - 1;
    while (left < right) {
        nodeAddress[left]->next = nodeAddress[right];
        ++left;
        if (left == right) {
            break;
        }
        nodeAddress[right]->next = nodeAddress[left];
        --right;
    }
    nodeAddress[left]->next = NULL;
}

int main(int argc, char** argv) {
#define MAX_NODES (5 * 10000)
    struct testCaseType {
        int node[MAX_NODES];
        int nodeSize;
    } testCase[] = {{{1, 2, 3, 4}, 4}, {{1, 2, 3, 4, 5}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [1,2,3,4]
     *  Output: [1,4,2,3]
     *
     *  Input: head = [1,2,3,4,5]
     *  Output: [1,5,2,4,3]
     */

    struct ListNode* pHead = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        reorderList(pHead);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
