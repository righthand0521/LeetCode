#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "tree.h"

bool dfs(struct ListNode* head, struct TreeNode* root) {
    bool retVal = false;

    if (head == NULL) {
        retVal = true;
    } else if (root == NULL) {
        retVal = false;
    } else if (head->val != root->val) {
        retVal = false;
    } else {
        retVal = dfs(head->next, root->left) || dfs(head->next, root->right);
    }

    return retVal;
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
bool isSubPath(struct ListNode* head, struct TreeNode* root) {
    bool retVal = false;

    if (root == NULL) {
        return retVal;
    }

    retVal = dfs(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int head[MAX_SIZE];
        int headSize;
        int root[MAX_SIZE];
        int rootSize;
    } testCase[] = {{{4, 2, 8},
                     3,
                     {1,       4,       4,       INT_MIN, 2,       2,       INT_MIN, INT_MAX, INT_MAX,
                      1,       INT_MIN, 6,       8,       INT_MIN, INT_MIN, INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MIN, INT_MIN, 1,       3},
                     27},
                    {{1, 4, 2, 6},
                     4,
                     {1,       4,       4,       INT_MIN, 2,       2,       INT_MIN, INT_MAX, INT_MAX,
                      1,       INT_MIN, 6,       8,       INT_MIN, INT_MIN, INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MIN, INT_MIN, 1,       3},
                     27},
                    {{1, 4, 2, 6, 8},
                     5,
                     {1,       4,       4,       INT_MIN, 2,       2,       INT_MIN, INT_MAX, INT_MAX,
                      1,       INT_MIN, 6,       8,       INT_MIN, INT_MIN, INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MIN, INT_MIN, 1,       3},
                     27}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
     *  Output: true
     *
     *  Input: head = [1,4,2,6], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
     *  utput: true
     *
     *  Input: head = [1,4,2,6,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
     *  Output: false
     */

    struct ListNode* pHead = NULL;
    struct TreeNode* pRoot = NULL;
    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].head, testCase[i].headSize);
        printf("Input: head = [");
        printList(pHead);
        printf("], root = [");
        for (j = 0; j < testCase[i].rootSize; ++j) {
            if (testCase[i].root[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
            } else if (testCase[i].root[j] == INT_MAX) {
                continue;
            } else {
                printf("%s%d", (j == 0 ? "" : ","), testCase[i].root[j]);
            }
        }
        printf("]\n");
        pRoot = buildBinaryTree(testCase[i].root, testCase[i].rootSize, 0);

        answer = isSubPath(pHead, pRoot);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        freeListNode(pHead);
        pHead = NULL;
        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
