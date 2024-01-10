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

struct ListNode* deleteDuplicates(struct ListNode* head) {
    if ((head == NULL) || (head->next == NULL)) {
        return head;
    }

    struct ListNode* p = head->next;
    struct ListNode* pPrevious = head;
    while (p != NULL) {
        if (p->val == pPrevious->val) {
            pPrevious->next = p->next;
            free(p);
            p = pPrevious->next;
        } else {
            pPrevious = p;
            p = p->next;
        }
    }

    return head;
}

int main(int argc, char** argv) {
    typedef struct ListNode* (*executeFunc)(struct ListNode*);
    const struct exampleType { executeFunc eFunc; } example[] = {{deleteDuplicates}};
    int numberOfExample = sizeof(example) / sizeof(example[0]);

#define MAX_NODES (300)
    struct testCaseType {
        int node[MAX_NODES];
        int nodeSize;
    } testCase[] = {{{1, 1, 2}, 3}, {{1, 1, 2, 3, 3}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    struct ListNode* pHead = NULL;
    struct ListNode* pAnswer = NULL;
    int idx_method;
    int idx_testData;
    int idx_testData_node;
    for (idx_method = 0; idx_method < numberOfExample; ++idx_method) {
        printf("== Method %d ==\n", idx_method + 1);
        printf("\n");

        for (idx_testData = 0; idx_testData < numberOfTestCase; ++idx_testData) {
            for (idx_testData_node = 0; idx_testData_node < testCase[idx_testData].nodeSize; ++idx_testData_node) {
                pHead = addValueToEnd(pHead, testCase[idx_testData].node[idx_testData_node]);
            }
            printf("Input: head = [");
            display(pHead);
            printf("]\n");

            pAnswer = example[idx_method].eFunc(pHead);
            printf("Output: [");
            display(pAnswer);
            printf("]\n");

            printf("\n");

            freeNode(pHead);
            pHead = NULL;
        }
    }

    return EXIT_SUCCESS;
}
