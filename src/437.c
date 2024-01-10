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
int dfs(struct TreeNode* root, long targetSum) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    if (root->val == targetSum) {
        retVal += 1;
    }
    retVal += dfs(root->left, targetSum - root->val);
    retVal += dfs(root->right, targetSum - root->val);

    return retVal;
}
int pathSum(struct TreeNode* root, int targetSum) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    retVal = dfs(root, targetSum);
    retVal += pathSum(root->left, targetSum);
    retVal += pathSum(root->right, targetSum);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int targetSum;
    } testCase[] = {{{10, 5, -3, 3, 2, INT_MIN, 11, 3, -2, INT_MIN, 1}, 11, 8},
                    {{5, 4, 8, 11, INT_MIN, 13, 4, 7, 2, INT_MIN, INT_MIN, 5, 1}, 13, 22}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
     *  Output: 3
     *
     *  Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
     *  Output: 3
     */

    struct TreeNode* pRoot = NULL;
    int answer = 0;
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

        answer = pathSum(pRoot, testCase[i].targetSum);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
