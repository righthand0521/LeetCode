#include <math.h>
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
int dfs(struct TreeNode* root, int maxAncestor, int minAncestor) {
    int retVal = maxAncestor - minAncestor;

    if (root == NULL) {
        return retVal;
    }

    maxAncestor = fmax(root->val, maxAncestor);
    minAncestor = fmin(root->val, minAncestor);
    int left = dfs(root->left, maxAncestor, minAncestor);
    int right = dfs(root->right, maxAncestor, minAncestor);
    retVal = fmax(left, right);

    return retVal;
}
int maxAncestorDiff(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }
    retVal = dfs(root, root->val, root->val);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {
        {{8, 3, 10, 1, 6, INT_MIN, 14, INT_MIN, INT_MIN, 4, 7, INT_MAX, INT_MAX, 13}, 14},
        {{1, INT_MIN, 2, INT_MAX, INT_MAX, INT_MIN, 0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 3}, 14}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
     *  Output: 7
     *
     *  Input: root = [1,null,2,null,0,3]
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
        printf("]\n");
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        answer = maxAncestorDiff(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
