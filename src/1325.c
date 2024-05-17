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
struct TreeNode* removeLeafNodes(struct TreeNode* root, int target) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        return pRetVal;
    }

    pRetVal->left = removeLeafNodes(pRetVal->left, target);
    pRetVal->right = removeLeafNodes(pRetVal->right, target);
    if ((pRetVal->left == NULL) && (pRetVal->right == NULL) && (pRetVal->val == target)) {
        free(pRetVal);
        pRetVal = NULL;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int target;
    } testCase[] = {{{1, 2, 3, 2, INT_MIN, 2, 4}, 7, 2},
                    {{1, 3, 3, 3, 2}, 5, 3},
                    {{1, 2, INT_MIN, 2, INT_MIN, INT_MAX, INT_MAX, 2}, 8, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,3,2,null,2,4], target = 2
     *  Output: [1,null,3,null,4]
     *
     *  Input: root = [1,3,3,3,2], target = 3
     *  Output: [1,3,null,null,2]
     *
     *  Input: root = [1,2,null,2,null,2], target = 2
     *  Output: [1]
     */

    struct TreeNode* pRoot = NULL;
    int height;
    struct TreeNode* pAnswer = NULL;
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
        printf("], target = %d\n", testCase[i].target);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        pAnswer = removeLeafNodes(pRoot, testCase[i].target);
        height = getTreeHeight(pAnswer);
        printf("Output: [");
        showTreeOutput(pAnswer, height);
        printf("]\n");

        printf("\n");

        freeTreeNode(pAnswer);
        pAnswer = NULL;
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
