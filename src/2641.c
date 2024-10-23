#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define MAX_NODES_SIZE (int)(1e5)  // The number of nodes in the tree is in the range [1, 10^5].
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* replaceValueInTree(struct TreeNode* root) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        return pRetVal;
    }

    int queueHead = 0;
    int queueTail = 0;
    struct TreeNode* queue[MAX_NODES_SIZE];
    memset(queue, 0, sizeof(queue));
    queue[queueTail++] = pRetVal;

    int levelSumsIndex = 0;
    int levelSums[MAX_NODES_SIZE];
    memset(levelSums, 0, sizeof(levelSums));

    struct TreeNode* currentNode;
    int levelSize;
    int levelSum = 0;
    while (queueHead < queueTail) {
        levelSum = 0;

        levelSize = queueTail - queueHead;
        for (int i = 0; i < levelSize; ++i) {
            currentNode = queue[queueHead++];

            levelSum += currentNode->val;
            if (currentNode->left) {
                queue[queueTail++] = currentNode->left;
            }
            if (currentNode->right) {
                queue[queueTail++] = currentNode->right;
            }
        }

        levelSums[levelSumsIndex++] = levelSum;
    }

    queueHead = 0;
    queueTail = 0;
    memset(queue, 0, sizeof(queue));
    queue[queueTail++] = pRetVal;

    pRetVal->val = 0;
    int levelIndex = 1;
    int siblingSum = 0;
    while (queueHead < queueTail) {
        levelSize = queueTail - queueHead;
        for (int i = 0; i < levelSize; ++i) {
            currentNode = queue[queueHead++];

            siblingSum = 0;
            siblingSum += ((currentNode->left != NULL) ? (currentNode->left->val) : (0));
            siblingSum += ((currentNode->right != NULL) ? (currentNode->right->val) : (0));

            if (currentNode->left) {
                currentNode->left->val = levelSums[levelIndex] - siblingSum;
                queue[queueTail++] = currentNode->left;
            }
            if (currentNode->right) {
                currentNode->right->val = levelSums[levelIndex] - siblingSum;
                queue[queueTail++] = currentNode->right;
            }
        }

        ++levelIndex;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{5, 4, 9, 1, 10, INT_MIN, 7}, 7}, {{3, 1, 2}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [5,4,9,1,10,null,7]
     *  Output: [0,0,0,7,7,null,11]
     *
     *  Input: root = [3,1,2]
     *  Output: [0,0,0]
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

        pRoot = replaceValueInTree(pRoot);
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
