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
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int dfs(struct TreeNode* root, int* returnMax) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    int left = dfs(root->left, returnMax);
    int right = dfs(root->right, returnMax);

    retVal = MAX((left + root->val), (right + root->val));
    retVal = MAX(retVal, root->val);

    (*returnMax) = MAX((*returnMax), MAX(retVal, (left + right + root->val)));

    return retVal;
}
int maxPathSum(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    retVal = INT_MIN;
#if (1)
    // https://leetcode.cn/problems/binary-tree-maximum-path-sum/solutions/298031/di-gui-zui-you-jie-bu-jing-guo-gen-jie-dian-de-chu/
    dfs(root, &retVal);
#else
    // https://leetcode.cn/problems/binary-tree-maximum-path-sum/solutions/1731711/by-xun-ge-v-7r1v/
    int left;
    int right;
    int val = root->val;

    if (root->left) {
        left = maxPathSum(root->left);
        retVal = MAX(retVal, left);
        val = MAX(val, (root->val + root->left->val));
    }

    if (root->right) {
        right = maxPathSum(root->right);
        retVal = MAX(retVal, right);
        val = MAX(val, (root->val + root->right->val));
    }

    if (root->left && root->right) {
        retVal = MAX(retVal, (root->val + root->left->val + root->right->val));
    }

    root->val = val;

    retVal = MAX(retVal, root->val);
#endif

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
