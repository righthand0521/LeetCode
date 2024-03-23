#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

int dfs(struct TreeNode* root, int* returnMax) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    int left = dfs(root->left, returnMax);
    int right = dfs(root->right, returnMax);
    retVal = fmax((left + root->val), (right + root->val));
    retVal = fmax(retVal, root->val);

    int maxValue = fmax(retVal, (left + right + root->val));
    (*returnMax) = fmax((*returnMax), maxValue);

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
int maxPathSum(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    retVal = INT_MIN;
    dfs(root, &retVal);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3}, 3}, {{-10, 9, 20, INT_MIN, INT_MIN, 15, 7}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,3]
     *  Output: 6
     *
     *  Input: root = [-10,9,20,null,null,15,7]
     *  Output: 42
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

        answer = maxPathSum(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
