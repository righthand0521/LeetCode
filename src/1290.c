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

int getDecimalValue(struct ListNode* head) {
    int retVal = head->val;

    struct ListNode* pCurrent = head->next;
    while (pCurrent != NULL) {
        retVal = (retVal << 1) | pCurrent->val;
        pCurrent = pCurrent->next;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (30)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{1, 0, 1}, 3}, {{0}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    struct ListNode* pHead = NULL;
    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: ");
        for (j = 0; j < testCase[i].nodeSize; ++j) {
            pHead = addValueToEnd(pHead, testCase[i].node[j]);
        }
        printf("head = [");
        display(pHead);
        printf("]\n");

        answer = getDecimalValue(pHead);
        printf("Output: %d\n", answer);

        printf("\n");

        freeNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}