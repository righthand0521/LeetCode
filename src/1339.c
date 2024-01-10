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
#define MODULO (int)(1e9 + 7)
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int postOrder(struct TreeNode* root, int* pSubTreeSum, int* returnSubTreeSumCount) {
    if (root == NULL) {
        return 0;
    }

    int retVal = postOrder(root->left, pSubTreeSum, returnSubTreeSumCount) +
                 postOrder(root->right, pSubTreeSum, returnSubTreeSumCount) + root->val;
    pSubTreeSum[(*returnSubTreeSumCount)++] = retVal;

    return retVal;
}
int maxProduct(struct TreeNode* root) {
    int retVal = 0;

#define MAX_NODE (50000)
    int subTreeSum[MAX_NODE];
    memset(subTreeSum, 0, sizeof(subTreeSum));
    int subTreeSumCount = 0;

    int treeSum = postOrder(root, subTreeSum, &subTreeSumCount);
    long long tmpRet = 0;
    int i;
    for (i = 0; i < subTreeSumCount; ++i) {
        tmpRet = MAX(tmpRet, ((long long)subTreeSum[i] * (long long)(treeSum - subTreeSum[i])));
    }
    retVal = tmpRet % MODULO;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {
        {{1, 2, 3, 4, 5, 6}, 6},
        {{1, INT_MIN, 2, INT_MAX, INT_MAX, 3, 4, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MIN, INT_MIN, 5, 6}, 15}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,3,4,5,6]
     *  Output: 110
     *
     *  Input: root = [1,null,2,3,4,null,null,5,6]
     *  Output: 90
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

        answer = maxProduct(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
