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
void inOrder(struct TreeNode* pRoot, long* pMin) {
    if (pRoot != NULL) {
        inOrder(pRoot->left, pMin);
        if ((long)(pRoot->val) > *pMin) {
            *pMin = pRoot->val;
        } else {
            *pMin = LONG_MAX;
        }
        inOrder(pRoot->right, pMin);
    }
}
bool isValidBST(struct TreeNode* root) {
    bool retVal = true;

    long minLeaf = LONG_MIN;
    inOrder(root, &minLeaf);
    if (minLeaf == LONG_MAX) {
        retVal = false;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 1, 3}, 3}, {{5, 1, 4, INT_MIN, INT_MIN, 3, 6}, 7}, {{1, 1}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [2,1,3]
     *  Output: true
     *
     *  Input: root = [5,1,4,null,null,3,6]
     *  Output: false
     */

    struct TreeNode* pRoot = NULL;
    bool pAnswer = true;
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

        pAnswer = isValidBST(pRoot);
        printf("Output: %s\n", (pAnswer == true ? "true" : "false"));

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
