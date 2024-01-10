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
struct TreeNode* searchBST(struct TreeNode* root, int val) {
    struct TreeNode* pRetVal = NULL;

    if (root == NULL) {
        return pRetVal;
    }

    if (root->val == val) {
        pRetVal = root;
    } else if (root->val > val) {
        pRetVal = searchBST(root->left, val);
    } else if (root->val < val) {
        pRetVal = searchBST(root->right, val);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int val;
    } testCase[] = {{{4, 2, 7, 1, 3}, 5, 2}, {{4, 2, 7, 1, 3}, 5, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [4,2,7,1,3], val = 2
     *  Output: [2,1,3]
     *
     *  Input: root = [4,2,7,1,3], val = 5
     *  Output: []
     */

    struct TreeNode* pRoot = NULL;
    int height;
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
        printf("], val = %d\n", testCase[i].val);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        pAnswer = searchBST(pRoot, testCase[i].val);
        height = getTreeHeight(pAnswer);
        printf("Output: [");
        showTreeOutput(pAnswer, height);
        printf("]\n");

        printf("\n");

        pAnswer = NULL;
        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
