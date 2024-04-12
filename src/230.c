#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void inorder(struct TreeNode* root, int* k, int* retVal) {
    if (root == NULL) {
        return;
    }

    inorder(root->left, k, retVal);
    (*k)--;
    if ((*k) == 0) {
        (*retVal) = root->val;
        return;
    }
    inorder(root->right, k, retVal);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int kthSmallest(struct TreeNode* root, int k) {
    int retVal = 0;

    inorder(root, &k, &retVal);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{3, 1, 4, INT_MIN, 2}, 5, 1}, {{5, 3, 6, 2, 4, INT_MIN, INT_MIN, 1}, 8, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [3,1,4,null,2], k = 1
     *  Output: 1
     *
     *  Input: root = [5,3,6,2,4,null,null,1], k = 3
     *  Output: 3
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
        printf("], k = %d\n", testCase[i].k);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        answer = kthSmallest(pRoot, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
