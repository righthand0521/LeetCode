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
struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        if (pRetVal == NULL) {
            perror("malloc");
            return pRetVal;
        }
        pRetVal->val = val;
        pRetVal->left = NULL;
        pRetVal->right = NULL;

        return pRetVal;
    }

    if (pRetVal->val > val) {
        pRetVal->left = insertIntoBST(pRetVal->left, val);
    } else if (pRetVal->val <= val) {
        pRetVal->right = insertIntoBST(pRetVal->right, val);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int val;
    } testCase[] = {{{4, 2, 7, 1, 3}, 5, 5}, {{40, 20, 60, 10, 30, 50, 70}, 7, 25}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [4,2,7,1,3], val = 5
     *  Output: [4,2,7,1,3,5]
     *
     *  Input: root = [40,20,60,10,30,50,70], val = 25
     *  Output: [40,20,60,10,30,50,70,null,null,25]
     */

    struct TreeNode* pRoot = NULL;
    int height;
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
        printf("], val = %d\n", testCase[i].val);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        pRoot = insertIntoBST(pRoot, testCase[i].val);
        height = getTreeHeight(pRoot);
        printf("Output: [");
        showTreeOutput(pRoot, height);
        printf("]\n");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
