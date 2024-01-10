#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode* next;
};
void display(struct ListNode* pHead) {
    struct ListNode* pCurrent = pHead;
    while (pCurrent != NULL) {
        printf("%d%s", pCurrent->val, (pCurrent->next == NULL) ? "" : ",");
        pCurrent = pCurrent->next;
    }
}
struct ListNode* createNode(int value) {
    struct ListNode* pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->val = value;
    pNew->next = NULL;

    return pNew;
}
void freeNode(struct ListNode* pHead) {
    struct ListNode* pCurrent = pHead;
    struct ListNode* pFree = NULL;
    while (pCurrent != NULL) {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        free(pFree);
    }
}
struct ListNode* addValueToEnd(struct ListNode* pHead, int value) {
    struct ListNode* pNew = createNode(value);
    if (pNew == NULL) {
        return pHead;
    }

    if (pHead == NULL) {
        pHead = pNew;
        return pHead;
    }

    struct ListNode* pCurrent = pHead;
    while (pCurrent->next != NULL) {
        pCurrent = pCurrent->next;
    }
    pCurrent->next = pNew;

    return pHead;
}
struct ListNode* rotateRight(struct ListNode* head, int k) {
    struct ListNode* pRetVal = head;

    if ((pRetVal == NULL) || (pRetVal->next == NULL)) {
        return pRetVal;
    }

    int headSize = 0;
#if 1  // Time Complexity: O(n) + O(k)
    while (pRetVal->next != NULL) {
        ++headSize;
        pRetVal = pRetVal->next;
    }
    k = headSize - (k % (headSize + 1));

    pRetVal->next = head;
    while (k--) {
        head = head->next;
    }
    pRetVal = head;
    head = head->next;
    pRetVal->next = NULL;
#else  // Time Complexity: O(n) + O(k*n)
    while (pRetVal != NULL) {
        ++headSize;
        pRetVal = pRetVal->next;
    }
    k = k % headSize;

    struct ListNode* pPrevious;
    int i;
    for (i = 0; i < k; ++i) {
        pRetVal = head;
        pPrevious = NULL;
        while (pRetVal->next != NULL) {
            pPrevious = pRetVal;
            pRetVal = pRetVal->next;
        }
        pPrevious->next = NULL;
        pRetVal->next = head;
        head = pRetVal;
    }
#endif

    return head;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
        int k;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5, 2}, {{0, 1, 2}, 3, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    struct ListNode* pHead = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        for (j = 0; j < testCase[i].nodeSize; ++j) {
            pHead = addValueToEnd(pHead, testCase[i].node[j]);
        }
        printf("Input: head = [");
        display(pHead);
        printf("], k = %d\n", testCase[i].k);

        pHead = rotateRight(pHead, testCase[i].k);
        printf("Output: [");
        display(pHead);
        printf("]\n");

        printf("\n");

        freeNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
