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
#define MAX_NODE (10000)
void inorder(struct TreeNode* root, int* pTreeNodeCount, int* pTreeArray) {
    if (root == NULL) {
        return;
    }
    inorder(root->left, pTreeNodeCount, pTreeArray);
    *(pTreeArray + (*pTreeNodeCount)) = root->val;
    (*pTreeNodeCount) = (*pTreeNodeCount) + 1;
    inorder(root->right, pTreeNodeCount, pTreeArray);
}
int kthSmallest(struct TreeNode* root, int k) {
    int retVal = 0;

    int* pTreeArray = (int*)malloc(MAX_NODE * sizeof(int));
    if (pTreeArray == NULL) {
        perror("malloc");
        return retVal;
    }
    int treeNodeCount = 0;
    inorder(root, &treeNodeCount, pTreeArray);
    if (k <= treeNodeCount) {
        retVal = *(pTreeArray + k - 1);
    }
    free(pTreeArray);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
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
