#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int compareListNode(const void* a, const void* b) {
    const struct ListNode* const* aa = a;
    const struct ListNode* const* bb = b;

    // ascending order
    return ((*aa)->val > (*bb)->val) - ((*aa)->val < (*bb)->val);
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* sortList(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    if ((head == NULL) || (head->next == NULL)) {
        return pRetVal;
    }

    int headSize = 0;
    struct ListNode* pNext = NULL;
    for (pNext = head; pNext != NULL; pNext = pNext->next) {
        ++headSize;
    }

    int i = 0;
    struct ListNode* address[headSize + 1];
    for (pNext = head; pNext != NULL; pNext = pNext->next) {
        address[i++] = pNext;
    }
    address[i] = NULL;
    qsort(address, headSize, sizeof(*address), compareListNode);
    for (i = 0; i < headSize; ++i) {
        address[i]->next = address[i + 1];
    }
    head = address[0];
    pRetVal = head;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_NODES (5 * 10000)
    struct testCaseType {
        int node[MAX_NODES];
        int nodeSize;
    } testCase[] = {{{4, 2, 1, 3}, 4}, {{-1, 5, 3, 4, 0}, 5}, {{}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [4,2,1,3]
     *  Output: [1,2,3,4]
     *
     *  Input: head = [-1,5,3,4,0]
     *  Output: [-1,0,3,4,5]
     *
     *  Input: head = []
     *  Output: []
     */

    struct ListNode* pHead = NULL;
    struct ListNode* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pAnswer = sortList(pHead);
        printf("Output: [");
        printList(pAnswer);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
