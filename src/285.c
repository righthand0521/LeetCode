#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* inorderSuccessor(struct TreeNode* root, struct TreeNode* p) {
    /* Algorithm
     *  If the value of the root node is less than or equal to the value of the p node,
     *  it means that the successor node of p must be in the right subtree,
     *  so this function is recursively called on the right child node.
     *
     *  If the value of the root node is greater than the value of p,
     *  then it is possible that the root node is the successor of p,
     *  or a node in the left subtree is a successor of p,
     *  * So first call this function recursively on the left child node,
     *  * If it returns empty, indicating that the root node is a successor node, just return,
     *  * If it is not empty, return that node
     */

    struct TreeNode* pRetVal = NULL;

    if (root == NULL) {
        return pRetVal;
    }

    if (root->val <= p->val) {
        pRetVal = inorderSuccessor(root->right, p);
    } else {
        pRetVal = inorderSuccessor(root->left, p);
        if (pRetVal == NULL) {
            pRetVal = root;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int p[1];
    } testCase[] = {
        {{2, 1, 3}, 3, {1}}, {{5, 3, 6, 2, 4, INT_MIN, INT_MIN, 1}, 8, {6}}, {{2, 1, 3}, 3, {2}}, {{2, 1}, 2, {1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [2,1,3], p = 1
     *  Output: 2
     *
     *  Input: root = [5,3,6,2,4,null,null,1], p = 6
     *  Output: null
     */

    struct TreeNode* pRoot = NULL;
    struct TreeNode* pNode = NULL;
    struct TreeNode* pAnswer = NULL;
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
        printf("], p = %d\n", testCase[i].p[0]);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);
        pNode = buildBinaryTree(testCase[i].p, 1, 0);

        pAnswer = inorderSuccessor(pRoot, pNode);
        if (pAnswer == NULL) {
            printf("Output: null\n");
        } else {
            printf("Output: %d\n", pAnswer->val);
        }
        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        freeTreeNode(pNode);
        pNode = NULL;
    }

    return EXIT_SUCCESS;
}
