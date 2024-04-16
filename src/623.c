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
struct TreeNode* addOneRow(struct TreeNode* root, int val, int depth) {
    struct TreeNode* pRetVal = root;

    if (depth == 1) {
        pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        if (pRetVal == NULL) {
            perror("malloc");
            return pRetVal;
        }
        pRetVal->val = val;
        pRetVal->left = root;
        pRetVal->right = NULL;
        return pRetVal;
    }

#define MAX_NODE_SIZE (int)(1e4)  // The number of nodes in the tree is in the range [1, 10^4].
    struct TreeNode** currentLevel = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * MAX_NODE_SIZE);
    if (currentLevel == NULL) {
        perror("malloc");
        return pRetVal;
    }
    int currentLevelHead = 0;
    int currentLevelTail = 0;
    currentLevel[currentLevelTail++] = root;

    int nodeCount = 0;
    int i, j;
    for (i = 1; i < (depth - 1); ++i) {
        nodeCount = currentLevelTail - currentLevelHead;
        for (j = 0; j < nodeCount; ++j) {
            if (currentLevel[currentLevelHead]->left != NULL) {
                currentLevel[currentLevelTail++] = currentLevel[currentLevelHead]->left;
            }
            if (currentLevel[currentLevelHead]->right != NULL) {
                currentLevel[currentLevelTail++] = currentLevel[currentLevelHead]->right;
            }
            currentLevelHead++;
        }
    }

    struct TreeNode* pNew = NULL;
    for (; currentLevelHead != currentLevelTail; currentLevelHead++) {
        pNew = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        if (pRetVal == NULL) {
            perror("malloc");
            break;
        }
        pNew->val = val;
        pNew->left = currentLevel[currentLevelHead]->left;
        pNew->right = NULL;
        currentLevel[currentLevelHead]->left = pNew;

        pNew = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        if (pRetVal == NULL) {
            perror("malloc");
            break;
        }
        pNew->val = val;
        pNew->left = NULL;
        pNew->right = currentLevel[currentLevelHead]->right;
        currentLevel[currentLevelHead]->right = pNew;
    }

    free(currentLevel);
    currentLevel = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int val;
        int depth;
    } testCase[] = {{{4, 2, 6, 3, 1, 5}, 6, 1, 2}, {{4, 2, INT_MIN, 3, 1}, 5, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [4,2,6,3,1,5], val = 1, depth = 2
     *  Output: [4,1,1,2,null,null,6,3,1,5]
     *
     *  Input: root = [4,2,null,3,1], val = 1, depth = 3
     *  Output: [4,2,null,1,1,3,null,null,1]
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
        printf("], val = %d, depth = %d\n", testCase[i].val, testCase[i].depth);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        pRoot = addOneRow(pRoot, testCase[i].val, testCase[i].depth);
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
