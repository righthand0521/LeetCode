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
bool evaluateTree(struct TreeNode* root) {
    bool retVal = false;

    if ((root->left == NULL) && (root->right == NULL)) {
        if (root->val == 0) {
            retVal = false;
        } else if (root->val == 1) {
            retVal = true;
        }

        return retVal;
    }

    if (root->val == 2) {
        retVal = (evaluateTree(root->left) | evaluateTree(root->right));
    } else if (root->val == 3) {
        retVal = (evaluateTree(root->left) & evaluateTree(root->right));
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 1, 3, INT_MIN, INT_MIN, 0, 1}, 7}, {{0}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [2,1,3,null,null,0,1]
     *  Output: true
     *
     *  Input: root = [0]
     *  Output: false
     */

    struct TreeNode* pRoot = NULL;
    bool answer = false;
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

        answer = evaluateTree(pRoot);
        printf("Output: %s\n", answer == true ? "true" : "false");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
