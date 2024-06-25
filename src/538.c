#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void plusTraversal(struct TreeNode* root, int* addValue) {
    if (root == NULL) {
        return;
    }

    plusTraversal(root->right, addValue);
    root->val += (*addValue);
    (*addValue) = root->val;
    plusTraversal(root->left, addValue);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* convertBST(struct TreeNode* root) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        return pRetVal;
    }
    int addValue = 0;
    plusTraversal(pRetVal, &addValue);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{4, 1, 6, 0, 2, 5, 7, INT_MIN, INT_MIN, INT_MIN, 3, INT_MIN, INT_MIN, INT_MIN, 8}, 15},
                    {{0, INT_MIN, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
     *  Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
     *
     *  Input: root = [0,null,1]
     *  Output: [1,null,1]
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
        printf("]\n");
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        pRoot = convertBST(pRoot);
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
