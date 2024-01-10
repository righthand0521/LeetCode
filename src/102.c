#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

int treeHeight(struct TreeNode* pRoot) {
    if (pRoot == NULL) {
        return 0;
    }

    int leftHeight = treeHeight(pRoot->left);
    int rightHeight = treeHeight(pRoot->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }

    return rightHeight + 1;
}
void treeLevel(struct TreeNode* pRoot, int level, int* pReturnArray, int* pReturnArrayIndex) {
    if (pRoot == NULL) {
        return;
    }

    if (level == 0) {
        if (pReturnArray != NULL) {
            pReturnArray[(*pReturnArrayIndex)] = pRoot->val;
        }
        (*pReturnArrayIndex)++;
    } else {
        treeLevel(pRoot->left, level - 1, pReturnArray, pReturnArrayIndex);
        treeLevel(pRoot->right, level - 1, pReturnArray, pReturnArrayIndex);
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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    if (root == NULL) {
        (*returnSize) = 0;
        return pRetVal;
    }

    //
    (*returnSize) = treeHeight(root);
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

    //
    int i;
    int index;
    int level;
    for (level = 0; level < (*returnSize); ++level) {
        pRetVal[level] = NULL;
        index = 0;
        treeLevel(root, level, pRetVal[level], &index);

        (*returnColumnSizes)[level] = index;
        pRetVal[level] = (int*)malloc(((*returnColumnSizes)[level]) * sizeof(int));
        if (pRetVal[level] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (i = 0; i < level - 1; ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            (*returnSize) = 0;
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[level], 0, ((*returnColumnSizes)[level]) * sizeof(int));

        index = 0;
        treeLevel(root, level, pRetVal[level], &index);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{3, 9, 20, INT_MIN, INT_MIN, 15, 7}, 7, 0, NULL}, {{1}, 1, 0, NULL}, {{}, 0, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [3,9,20,null,null,15,7]
     *  Output: [[3],[9,20],[15,7]]
     *
     *  Input: root = [1]
     *  Output: [[1]]
     *
     *  Input: root = []
     *  Output: []
     */

    struct TreeNode* pRoot = NULL;
    int** pAnswer = NULL;
    int i, j, k;
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

        pAnswer = levelOrder(pRoot, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
