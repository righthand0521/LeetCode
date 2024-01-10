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
struct ListNode* deleteDuplicatesUnsorted(struct ListNode* head) {
    struct ListNode* pRetVal = head;

    if ((head == NULL) || (head->next == NULL)) {
        return pRetVal;
    }

#define MAX_HASH_SIZE (int)(1e5 + 1)
    int HashTable[MAX_HASH_SIZE];
    memset(HashTable, 0, sizeof(HashTable));
    while (pRetVal != NULL) {
        ++HashTable[pRetVal->val];
        pRetVal = pRetVal->next;
    }
    pRetVal = head;

    struct ListNode* pPrevious = head;
    while (pRetVal != NULL) {
        if (pRetVal == head) {
            if (HashTable[pRetVal->val] != 1) {
                head = head->next;
                pPrevious = head;
                free(pRetVal);
                pRetVal = head;
            } else {
                pRetVal = pRetVal->next;
            }
        } else {
            if (HashTable[pRetVal->val] != 1) {
                pPrevious->next = pRetVal->next;
                free(pRetVal);
                pRetVal = pPrevious->next;
            } else {
                pPrevious = pPrevious->next;
                pRetVal = pRetVal->next;
            }
        }
    }
    pRetVal = head;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {
        {{1, 2, 3, 2}, 4}, {{2, 1, 1, 2}, 4}, {{3, 2, 2, 1, 3, 2, 4}, 7}, {{}, 0},           {{1}, 1},
        {{1, 1, 1}, 3},    {{1, 2, 3}, 3},    {{1, 2, 3, 1}, 4},          {{1, 1, 2, 3}, 4}, {{1, 2, 3, 3}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    struct ListNode* pHead = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        for (j = 0; j < testCase[i].numsSize; ++j) {
            pHead = addValueToEndListNode(pHead, testCase[i].nums[j]);
        }
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pHead = deleteDuplicatesUnsorted(pHead);
        printf("Output: [");
        printList(pHead);
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
    }
    printf("\n");

    return EXIT_SUCCESS;
}
