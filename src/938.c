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
void inorder(struct TreeNode* root, int low, int high, int* sum) {
    if (root == NULL) {
        return;
    }

    inorder(root->left, low, high, sum);
    if ((root->val >= low) && (root->val <= high)) {
        (*sum) += root->val;
    }
    inorder(root->right, low, high, sum);
}
int rangeSumBST(struct TreeNode* root, int low, int high) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    inorder(root, low, high, &retVal);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int low;
        int high;
    } testCase[] = {{{10, 5, 15, 3, 7, INT_MIN, 18}, 7, 7, 15}, {{10, 5, 15, 3, 7, 13, 18, 1, INT_MIN, 6}, 10, 6, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
     *  Output: 32
     *
     *  Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
     *  Output: 23
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
        printf("], low = %d, high = %d\n", testCase[i].low, testCase[i].high);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        answer = rangeSumBST(pRoot, testCase[i].low, testCase[i].high);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
