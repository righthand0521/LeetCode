#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define RECURSIVE (0)
#define ITERATIVE (1)
void inorder(struct TreeNode* root, int* pTreeNodeCount, int* pTreeArray) {
#if (RECURSIVE)
    printf("RECURSIVE\n");

    if (root == NULL) {
        return;
    }
    inorder(root->left, pTreeNodeCount, pTreeArray);
    *(pTreeArray + (*pTreeNodeCount)) = root->val;
    (*pTreeNodeCount) = (*pTreeNodeCount) + 1;
    inorder(root->right, pTreeNodeCount, pTreeArray);
#elif (ITERATIVE)
    printf("ITERATIVE\n");

    // The number of nodes in the tree is in the range [0, 100].
    struct TreeNode** stackKeep = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 100);
    int top = 0;
    while ((root != NULL) || (top > 0)) {
        while (root != NULL) {
            stackKeep[top++] = root;
            root = root->left;
        }
        root = stackKeep[--top];
        *(pTreeArray + (*pTreeNodeCount)) = root->val;
        (*pTreeNodeCount) = (*pTreeNodeCount) + 1;
        root = root->right;
    }

    free(stackKeep);
    stackKeep = NULL;
#endif
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
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
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
    inorder(root, returnSize, pRetVal);

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
     *  Output: [1,3,2]
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

        pAnswer = inorderTraversal(pRoot, &testCase[i].returnSize);
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
