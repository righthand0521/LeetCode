#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

int treeHeight(struct TreeNode* pRoot) {
    int retVal = 0;

    if (pRoot == NULL) {
        return retVal;
    }

    int leftHeight = treeHeight(pRoot->left);
    int rightHeight = treeHeight(pRoot->right);
    if (leftHeight > rightHeight) {
        retVal = leftHeight + 1;
    } else {
        retVal = rightHeight + 1;
    }

    return retVal;
}
void treeLevel(struct TreeNode* pRoot, int level, int* pRetVal) {
    if (pRoot == NULL) {
        return;
    }

    if (level == 0) {
        (*pRetVal) = pRoot->val;
    } else {
        treeLevel(pRoot->left, level - 1, pRetVal);
        treeLevel(pRoot->right, level - 1, pRetVal);
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    if (root == NULL) {
        return pRetVal;
    }

    //
    (*returnSize) = treeHeight(root);
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        (*returnSize) = 0;
        return pRetVal;
    }

    //
    int value;
    int level;
    for (level = 0; level < (*returnSize); ++level) {
        treeLevel(root, level, &value);
        pRetVal[level] = value;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, 2, 3, INT_MIN, 5, INT_MIN, 4}, 7, 0}, {{1, INT_MIN, 3}, 3, 0}, {{}, 0, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,3,null,5,null,4]
     *  Output: [1,3,4]
     *
     *  Input: root = [1,null,3]
     *  Output: [1,3]
     *
     *  Input: root = []
     *  Output: []
     */

    struct TreeNode* pRoot = NULL;
    int* pAnswer = NULL;
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

        pAnswer = rightSideView(pRoot, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
