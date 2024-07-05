#include <limits.h>
#include <math.h>
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nodesBetweenCriticalPoints(struct ListNode* head, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc(2 * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, -1, (2 * sizeof(int)));
    (*returnSize) = 2;

    // The number of nodes in the list is in the range [2, 10^5].
    int currentIndex = 1;
    struct ListNode* pCurrent = head->next;
    struct ListNode* pPrevious = head;

    int firstCriticalIndex = 0;
    int previousCriticalIndex = 0;
    int minDistance = INT_MAX;
    while (pCurrent->next != NULL) {
        if (((pCurrent->val < pPrevious->val) && (pCurrent->val < pCurrent->next->val)) ||
            ((pCurrent->val > pPrevious->val) && (pCurrent->val > pCurrent->next->val))) {
            if (previousCriticalIndex == 0) {
                previousCriticalIndex = currentIndex;
                firstCriticalIndex = currentIndex;
            } else {
                minDistance = fmin(minDistance, currentIndex - previousCriticalIndex);
                previousCriticalIndex = currentIndex;
            }
        }

        currentIndex += 1;
        pPrevious = pCurrent;
        pCurrent = pCurrent->next;
    }

    int maxDistance;
    if (minDistance != INT_MAX) {
        maxDistance = previousCriticalIndex - firstCriticalIndex;
        pRetVal[0] = minDistance;
        pRetVal[1] = maxDistance;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{3, 1}, 2, 0}, {{5, 3, 1, 2, 5, 1, 2}, 7, 0}, {{1, 3, 2, 2, 3, 2, 2, 2, 7}, 9, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [3,1]
     *  Output: [-1,-1]
     *
     *  Input: head = [5,3,1,2,5,1,2]
     *  Output: [1,3]
     *
     *  Input: head = [1,3,2,2,3,2,2,2,7]
     *  Output: [3,3]
     */

    int* pAnswer = NULL;
    struct ListNode* pHead = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].nums, testCase[i].numsSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pAnswer = nodesBetweenCriticalPoints(pHead, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
