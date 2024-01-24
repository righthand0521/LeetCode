#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void preorder(struct TreeNode* root, int mask, int* returnCount) {
    if (root == NULL) {
        return;
    }

    mask = mask ^ (1 << root->val);  // 1 <= Node.val <= 9
    if ((root->left == NULL) && (root->right == NULL)) {
        if ((mask & (mask - 1)) == 0) {
            (*returnCount)++;
        }
        return;
    }
    preorder(root->left, mask, returnCount);
    preorder(root->right, mask, returnCount);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int pseudoPalindromicPaths(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }
    preorder(root, 0, &retVal);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 3, 1, 3, 1, INT_MIN, 1}, 7},
                    {{2, 1, 1, 1, 3, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 1}, 11},
                    {{9}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [2,3,1,3,1,null,1]
     *  Output: 2
     *
     *  Input: root = [2,1,1,1,3,null,null,null,null,null,1]
     *  Output: 1
     *
     *  Input: root = [9]
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

        answer = pseudoPalindromicPaths(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
