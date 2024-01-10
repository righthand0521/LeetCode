#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void preorder(struct TreeNode* root, int* pTreeNodeCount, int* pTreeArray) {
    if (root == NULL) {
        return;
    }
    *(pTreeArray + (*pTreeNodeCount)) = root->val;
    (*pTreeNodeCount) = (*pTreeNodeCount) + 1;
    preorder(root->left, pTreeNodeCount, pTreeArray);
    preorder(root->right, pTreeNodeCount, pTreeArray);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    if (root == NULL) {
        return pRetVal;
    }

    // The number of nodes in the tree is in the range [0, 100].
    pRetVal = (int*)malloc(100 * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    preorder(root, returnSize, pRetVal);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, INT_MIN, 2, INT_MAX, INT_MAX, 3}, 6, 0}, {{}, 0, 0}, {{1}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,null,2,3]
     *  Output: [1,2,3]
     *
     *  Input: root = []
     *  Output: []
     *
     *  Input: root = [1]
     *  Output: [1]
     */

    struct TreeNode* pRoot = NULL;
    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: root = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            if (testCase[i].nums[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
            } else if (testCase[i].nums[j] == INT_MAX) {
                continue;
            } else {
                printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
            }
        }
        printf("]\n");
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        pAnswer = preorderTraversal(pRoot, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
