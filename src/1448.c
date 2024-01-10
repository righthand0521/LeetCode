#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

int dfs(struct TreeNode* root, int maxValue) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    if (root->val >= maxValue) {
        retVal++;
        maxValue = root->val;
    }
    int left = dfs(root->left, maxValue);
    int right = dfs(root->right, maxValue);
    retVal += (left + right);

    return retVal;
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int goodNodes(struct TreeNode* root) {
    int retVal = 0;

    int maxValue = INT_MIN;  // Each node's value is between [-10^4, 10^4].
    retVal += dfs(root, maxValue);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 1, 4, 3, INT_MIN, INT_MIN, 1, 5}, 8}, {{3, 3, INT_MIN, 4, 2}, 5}, {{1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [3,1,4,3,null,1,5]
     *  Output: 4
     *
     *  Input: root = [3,3,null,4,2]
     *  Output: 3
     *
     *  Input: root = [1]
     *  Output: 1
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

        answer = goodNodes(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
