#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void inorderTraversal(struct TreeNode* root, int* inorder, int* inorderSize) {
    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left, inorder, inorderSize);
    inorder[(*inorderSize)] = root->val;
    (*inorderSize) += 1;
    inorderTraversal(root->right, inorder, inorderSize);
}
struct TreeNode* createBalancedBST(int* inorder, int start, int end) {
    struct TreeNode* pRetVal = NULL;

    // Base case: if the start index is greater than the end index, return NULL
    if (start > end) {
        return pRetVal;
    }

    // Find the middle element of the current range
    int mid = start + (end - start) / 2;
    // Recursively construct the left and right subtrees
    struct TreeNode* leftSubtree = createBalancedBST(inorder, start, mid - 1);
    struct TreeNode* rightSubtree = createBalancedBST(inorder, mid + 1, end);
    // Create a new node with the middle element and attach the subtrees
    pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = inorder[mid];
    pRetVal->left = leftSubtree;
    pRetVal->right = rightSubtree;

    return pRetVal;
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* balanceBST(struct TreeNode* root) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        return pRetVal;
    }

#define MAX_TREE_NODE (int)(1e4)  // The number of nodes in the tree is in the range [1, 10^4].
    // Create a vector to store the inorder traversal of the BST
    int inorder[MAX_TREE_NODE];
    memset(inorder, 0, sizeof(inorder));
    int inorderSize = 0;
    inorderTraversal(root, inorder, &inorderSize);

    // Construct and return the balanced BST
    pRetVal = createBalancedBST(inorder, 0, inorderSize - 1);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, INT_MIN, 2, INT_MAX, INT_MAX, INT_MIN, 3, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
                      INT_MIN, 4, INT_MIN, INT_MIN},
                     17},
                    {{2, 1, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,null,2,null,3,null,4,null,null]
     *  Output: [2,1,3,null,null,null,4]
     *
     *  Input: root = [2,1,3]
     *  Output: [2,1,3]
     */

    struct TreeNode* pRoot = NULL;
    struct TreeNode* pAnswer = NULL;
    int height;
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

        pAnswer = balanceBST(pRoot);
        height = getTreeHeight(pAnswer);
        printf("Output: [");
        showTreeOutput(pAnswer, height);
        printf("]\n");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        freeTreeNode(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
