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
void deleteNode(struct ListNode* node) {
    if ((node == NULL) || (node->next == NULL)) {
        return;
    }

    struct ListNode* p = node->next;
    *node = *node->next;
    free(p);
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
        int deleteVal;
    } testCase[] = {{{4, 5, 1, 9}, 4, 5}, {{4, 5, 1, 9}, 4, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [4,5,1,9], node = 5
     *  Output: [4,1,9]
     *
     *  Input: head = [4,5,1,9], node = 1
     *  Output: [4,5,9]
     */

    struct ListNode* pNode = NULL;
    struct ListNode* pHead = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        for (j = 0; j < testCase[i].nodeSize; ++j) {
            pHead = addValueToEndListNode(pHead, testCase[i].node[j]);
        }
        printf("Input: head = [");
        printList(pHead);
        printf("], node = %d\n", testCase[i].deleteVal);

        pNode = pHead;
        while (pNode != NULL) {
            if (pNode->val == testCase[i].deleteVal) {
                break;
            }
            pNode = pNode->next;
        }

        deleteNode(pNode);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
