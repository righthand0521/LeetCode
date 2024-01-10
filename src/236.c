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
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    struct TreeNode* pRetVal = root;

    if ((root == NULL) || (root == p) || (root == q)) {
        return pRetVal;
    }

    struct TreeNode* pLeft = lowestCommonAncestor(root->left, p, q);
    struct TreeNode* pRight = lowestCommonAncestor(root->right, p, q);
    if ((pLeft == NULL) && (pRight == NULL)) {
        pRetVal = NULL;
    } else if (pLeft == NULL) {
        pRetVal = pRight;
    } else if (pRight == NULL) {
        pRetVal = pLeft;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int p;
        int q;
    } testCase[] = {{{3, 5, 1, 6, 2, 0, 8, INT_MIN, INT_MIN, 7, 4}, 11, 5, 1},
                    {{3, 5, 1, 6, 2, 0, 8, INT_MIN, INT_MIN, 7, 4}, 11, 5, 4},
                    {{1, 2}, 2, 1, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
     *  Output: 3
     *
     *  Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
     *  Output: 5
     *
     *  Input: root = [1,2], p = 1, q = 2
     *  Output: 1
     */

    struct TreeNode* pRoot = NULL;
    struct TreeNode* pTree = NULL;
    struct TreeNode* qTree = NULL;
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
        printf("], p = %d, q = %d\n", testCase[i].p, testCase[i].q);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);
        findSubTree(pRoot, testCase[i].p, &pTree);
        findSubTree(pRoot, testCase[i].q, &qTree);

        pAnswer = lowestCommonAncestor(pRoot, pTree, qTree);
        printf("Output: %d\n", pAnswer->val);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        pTree = NULL;
        qTree = NULL;
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
