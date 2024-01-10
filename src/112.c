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
bool hasPathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL) {
        return false;
    }

    if ((root->left == NULL) && (root->right == NULL)) {
        if (root->val == targetSum) {
            return true;
        }
    }
    targetSum -= root->val;

    return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int targetSum;
    } testCase[] = {{{5, 4, 8, 11, INT_MIN, 13, 4, 7, 2, INT_MIN, INT_MIN, INT_MIN, INT_MAX, INT_MAX, 1}, 15, 22},
                    {{1, 2, 3}, 3, 5},
                    {{}, 0, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
     *  Output: true
     *
     *  Input: root = [1,2,3], targetSum = 5
     *  Output: false
     *
     *  Input: root = [], targetSum = 0
     *  Output: false
     */

    struct TreeNode* pRoot = NULL;
    bool answer = 0;
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
        printf("], targetSum = %d\n", testCase[i].targetSum);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        answer = hasPathSum(pRoot, testCase[i].targetSum);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
