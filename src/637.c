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
double* averageOfLevels(struct TreeNode* root, int* returnSize) {
    double* pRetVal = NULL;

    (*returnSize) = 0;

    if (root == NULL) {
        return pRetVal;
    }
    int treeLevel = treeHeight(root);
    pRetVal = (double*)malloc(treeLevel * sizeof(double));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, treeLevel * sizeof(double));

    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    int bfsQueueSize = 10001;  // 1 << treeLevel
    struct TreeNode* bfsQueue[bfsQueueSize];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    bfsQueue[bfsQueueTail] = root;
    bfsQueueTail++;

    int i;
    struct TreeNode* pNode;
    int currentLevelSize;
    double sum;
    while (bfsQueueHead < bfsQueueTail) {
        sum = 0;
        currentLevelSize = bfsQueueTail - bfsQueueHead;
        for (i = 0; i < currentLevelSize; ++i) {
            pNode = bfsQueue[bfsQueueHead];
            bfsQueueHead++;
            sum += pNode->val;

            if (pNode->left != NULL) {
                bfsQueue[bfsQueueTail] = pNode->left;
                bfsQueueTail++;
            }
            if (pNode->right != NULL) {
                bfsQueue[bfsQueueTail] = pNode->right;
                bfsQueueTail++;
            }
        }

        pRetVal[(*returnSize)] = sum / currentLevelSize;
        (*returnSize) += 1;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{3, 9, 20, INT_MIN, INT_MIN, 15, 7}, 7, 0}, {{3, 9, 20, 15, 7}, 5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [3,9,20,null,null,15,7]
     *  Output: [3.00000,14.50000,11.00000]
     *
     *  Input: root = [3,9,20,15,7]
     *  Output: [3.00000,14.50000,11.00000]
     */

    struct TreeNode* pRoot = NULL;
    double* pAnswer = NULL;
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

        pAnswer = averageOfLevels(pRoot, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%.5f", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
