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
struct TreeNode* reverseOddLevels(struct TreeNode* root) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        return pRetVal;
    }

    int bfsQueueSize = 1 << 14;  // The number of nodes in the tree is in the range [1, 2^14].
    struct TreeNode* bfsQueue[bfsQueueSize];
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueTail++] = pRetVal;

    int left, right, temp;
    struct TreeNode* pNode;
    int currentLevelNodesSize;
    int level = 0;
    while (bfsQueueTail > bfsQueueHead) {
        currentLevelNodesSize = bfsQueueTail - bfsQueueHead;
        struct TreeNode* currentLevelNodes[currentLevelNodesSize];
        for (int i = 0; i < currentLevelNodesSize; i++) {
            pNode = bfsQueue[bfsQueueHead++];

            currentLevelNodes[i] = pNode;
            if (pNode->left) {
                bfsQueue[bfsQueueTail++] = pNode->left;
            }
            if (pNode->right) {
                bfsQueue[bfsQueueTail++] = pNode->right;
            }
        }

        if (level % 2 == 1) {
            left = 0;
            right = currentLevelNodesSize - 1;
            while (left < right) {
                temp = currentLevelNodes[left]->val;
                currentLevelNodes[left]->val = currentLevelNodes[right]->val;
                currentLevelNodes[right]->val = temp;
                left++;
                right--;
            }
        }

        level++;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {
        {{2, 3, 5, 8, 13, 21, 34}, 7}, {{7, 13, 11}, 3}, {{0, 1, 2, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2}, 15}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [2,3,5,8,13,21,34]
     *  Output: [2,5,3,8,13,21,34]
     *
     *  Input: root = [7,13,11]
     *  Output: [7,11,13]
     *
     *  Input: root = [0,1,2,0,0,0,0,1,1,1,1,2,2,2,2]
     *  Output: [0,2,1,0,0,0,0,2,2,2,2,1,1,1,1]
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

        pRoot = reverseOddLevels(pRoot);
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
