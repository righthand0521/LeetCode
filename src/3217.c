#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define MAX_NUMS_SIZE (int)(1e5 + 1)  // 1 <= nums[i] <= 10^5
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* modifiedList(int* nums, int numsSize, struct ListNode* head) {
    struct ListNode* pRetVal = head;

    int valuesToRemove[MAX_NUMS_SIZE];
    memset(valuesToRemove, 0, sizeof(valuesToRemove));
    int i;
    for (i = 0; i < numsSize; ++i) {
        valuesToRemove[nums[i]] += 1;
    }

    struct ListNode* pDelete = NULL;
    while ((pRetVal != NULL) && (valuesToRemove[pRetVal->val] > 0)) {
        pDelete = pRetVal;
        pRetVal = pRetVal->next;
        free(pDelete);
        pDelete = NULL;
    }
    if (pRetVal == NULL) {
        return pRetVal;
    }

    struct ListNode* pCurrent = pRetVal;
    while (pCurrent->next != NULL) {
        if (valuesToRemove[pCurrent->next->val] > 0) {
            pDelete = pCurrent->next;
            pCurrent->next = pCurrent->next->next;
            free(pDelete);
            pDelete = NULL;
        } else {
            pCurrent = pCurrent->next;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 2, 3}, 3, {1, 2, 3, 4, 5}, 5}, {{1}, 1, {1, 2, 1, 2, 1, 2}, 6}, {{5}, 1, {1, 2, 3, 4}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3], head = [1,2,3,4,5]
     *  Output: [4,5]
     *
     *  Input: nums = [1], head = [1,2,1,2,1,2]
     *  Output: [2,2,2]
     *
     *  Input: nums = [5], head = [1,2,3,4]
     *  Output: [1,2,3,4]
     */

    struct ListNode* pHead = NULL;
    struct ListNode* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], head = [");
        printList(pHead);
        printf("]\n");

        pAnswer = modifiedList(testCase[i].nums, testCase[i].numsSize, pHead);
        printf("Output: [");
        printList(pAnswer);
        printf("]\n");

        printf("\n");

        freeListNode(pAnswer);
        pAnswer = NULL;
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
