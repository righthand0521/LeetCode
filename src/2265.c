#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void postorder(struct TreeNode* root, int* subtreeSum, int* subtreeNode, int* answer) {
    if (root == NULL) {
        (*subtreeSum) = 0;
        (*subtreeNode) = 0;
        return;
    }

    int leftSum, leftNode;
    postorder(root->left, &leftSum, &leftNode, answer);
    int rightSum, rightNode = 0;
    postorder(root->right, &rightSum, &rightNode, answer);

    (*subtreeSum) = leftSum + rightSum + root->val;
    (*subtreeNode) = leftNode + rightNode + 1;
    if (root->val == (*subtreeSum) / (*subtreeNode)) {
        (*answer) += 1;
    }
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int averageOfSubtree(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    int subtreeSum = 0;
    int subtreeNode = 0;
    postorder(root, &subtreeSum, &subtreeNode, &retVal);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{4, 8, 5, 0, 1, INT_MIN, 6}, 7}, {{1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [4,8,5,0,1,null,6]
     *  Output: 5
     *
     *  Input: root = [1]
     *  Output: 1
     */

    struct TreeNode* pRoot = NULL;
    int answer;
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

        answer = averageOfSubtree(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
