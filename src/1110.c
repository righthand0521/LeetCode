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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** delNodes(struct TreeNode* root, int* to_delete, int to_deleteSize, int* returnSize) {
    struct TreeNode** pRetVal = NULL;

    (*returnSize) = 0;

    //
    if (root == NULL) {
        return pRetVal;
    }

    //
    int maxReturnSize = 1000 + 1;  // The number of nodes in the given tree is at most 1000.
    pRetVal = (struct TreeNode**)malloc(maxReturnSize * sizeof(struct TreeNode*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    //
    int toDeleteSetSize = 1000 + 1;  // to_delete contains distinct values between 1 and 1000.
    int toDeleteSet[toDeleteSetSize];
    memset(toDeleteSet, 0, sizeof(toDeleteSet));
    int i;
    for (i = 0; i < to_deleteSize; ++i) {
        toDeleteSet[to_delete[i]] = 1;
    }

    //
    int nodesQueueSize = 1000 + 1;  // The number of nodes in the given tree is at most 1000.
    int nodesQueueHead = 0;
    int nodesQueueTail = 0;
    struct TreeNode* nodesQueue[nodesQueueSize];
    memset(nodesQueue, 0, sizeof(nodesQueue));
    nodesQueue[nodesQueueTail++] = root;

    //
    struct TreeNode* currentNode;
    while (nodesQueueHead < nodesQueueTail) {
        currentNode = nodesQueue[nodesQueueHead++];

        if (currentNode->left != NULL) {
            nodesQueue[nodesQueueTail++] = currentNode->left;
            // Disconnect the left child if it needs to be deleted
            if (toDeleteSet[currentNode->left->val] == 1) {
                currentNode->left = NULL;
            }
        }

        if (currentNode->right != NULL) {
            nodesQueue[nodesQueueTail++] = currentNode->right;
            // Disconnect the right child if it needs to be deleted
            if (toDeleteSet[currentNode->right->val] == 1) {
                currentNode->right = NULL;
            }
        }

        // If the current node needs to be deleted, add its non-null children to the forest
        if (toDeleteSet[currentNode->val] == 1) {
            if (currentNode->left != NULL) {
                pRetVal[(*returnSize)] = currentNode->left;
                (*returnSize) += 1;
            }
            if (currentNode->right != NULL) {
                pRetVal[(*returnSize)] = currentNode->right;
                (*returnSize) += 1;
            }

            if (currentNode != root) {
                free(currentNode);
                currentNode = NULL;
            }
        }
    }

    // Ensure the root is added to the forest if it is not to be deleted
    if (toDeleteSet[root->val] != 1) {
        pRetVal[(*returnSize)] = root;
        (*returnSize) += 1;
    } else {
        free(root);
        root = NULL;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int to_delete[MAX_SIZE];
        int to_deleteSize;
        int returnSize;
    } testCase[] = {{{1, 2, 3, 4, 5, 6, 7}, 7, {3, 5}, 2, 0},
                    {{1, 2, 4, INT_MIN, 3}, 5, {3}, 1, 0},
                    {{1, 2, 3, INT_MIN, INT_MIN, INT_MIN, 4}, 7, {2, 1}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
     *  Output: [[1,2,null,4],[6],[7]]
     *
     *  Input: root = [1,2,4,null,3], to_delete = [3]
     *  Output: [[1,2,4]]
     *
     *  Input: root = [1,2,3,null,null,null,4], to_delete = [2,1]
     *  Output: [[3,null,4]]
     */

    struct TreeNode* pRoot = NULL;
    struct TreeNode** pAnswer = NULL;
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
        printf("], to_delete = [");
        for (j = 0; j < testCase[i].to_deleteSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].to_delete[j]);
        }
        printf("]\n");
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        pAnswer = delNodes(pRoot, testCase[i].to_delete, testCase[i].to_deleteSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            height = getTreeHeight(pAnswer[j]);
            showTreeOutput(pAnswer[j], height);
            printf("]");
            freeTreeNode(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
