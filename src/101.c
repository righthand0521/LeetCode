#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

bool isMirror(struct TreeNode* left, struct TreeNode* right) {
    bool retVal = false;

    if ((left == NULL) && (right == NULL)) {
        retVal = true;
        return retVal;
    } else if ((left == NULL) || (right == NULL)) {
        return retVal;
    } else if (left->val != right->val) {
        return retVal;
    }
    retVal = (isMirror(left->left, right->right)) && (isMirror(left->right, right->left));

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
bool isSymmetric(struct TreeNode* root) {
    bool retVal = true;

    if (root == NULL) {
        return retVal;
    }
    retVal = isMirror(root->left, root->right);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 2, 3, 4, 4, 3}, 7}, {{1, 2, 2, INT_MIN, 3, INT_MIN, 3}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,2,3,4,4,3]
     *  Output: true
     *
     *  Input: root = [1,2,2,null,3,null,3]
     *  Output: false
     */

    struct TreeNode* pRoot = NULL;
    bool answer = true;
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

        answer = isSymmetric(pRoot);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
