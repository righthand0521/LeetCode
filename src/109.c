#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "tree.h"

struct TreeNode* buildBinarySearchTree(struct ListNode** pHead, int left, int right) {
    struct TreeNode* pRetVal = NULL;

    if (left > right) {
        return pRetVal;
    }
    int middle = (left + right + 1) / 2;

    pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    // Binary Tree Inorder Traversal: left -> root -> right
    pRetVal->left = buildBinarySearchTree(pHead, left, middle - 1);
    pRetVal->val = (*pHead)->val;
    (*pHead) = (*pHead)->next;
    pRetVal->right = buildBinarySearchTree(pHead, middle + 1, right);

    return pRetVal;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* sortedListToBST(struct ListNode* head) {
    struct TreeNode* pRetVal = NULL;

    struct ListNode* pNext = head;
    int listLength = 0;
    while (pNext != NULL) {
        ++listLength;
        pNext = pNext->next;
    }
    pRetVal = buildBinarySearchTree(&head, 0, listLength - 1);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20000)
    struct testCaseType {
        int node[MAX_SIZE];
        int nodeSize;
    } testCase[] = {{{-10, -3, 0, 5, 9}, 5}, {{}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [-10,-3,0,5,9]
     *  Output: [0,-3,9,-10,null,5]
     *
     *  Input: head = []
     *  Output: []
     */

    struct ListNode* pHead = NULL;
    struct TreeNode* pAnswer = NULL;
    int height;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].node, testCase[i].nodeSize);
        printf("Input: head = [");
        printList(pHead);
        printf("]\n");

        pAnswer = sortedListToBST(pHead);
        height = getTreeHeight(pAnswer);
        printf("Output: [");
        showTreeOutput(pAnswer, height);
        printf("]\n");

        printf("\n");

        freeTreeNode(pAnswer);
        pAnswer = NULL;
        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
