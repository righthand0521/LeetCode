#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void traverseLeftToRight(struct TreeNode* node, int currentHeight, int* maxHeightAfterRemoval, int* currentMaxHeight) {
    if (node == NULL) {
        return;
    }

    // Store the maximum height if this node were removed
    maxHeightAfterRemoval[node->val] = (*currentMaxHeight);

    // Update the current maximum height
    (*currentMaxHeight) = fmax((*currentMaxHeight), currentHeight);

    // Traverse left subtree first, then right
    traverseLeftToRight(node->left, currentHeight + 1, maxHeightAfterRemoval, currentMaxHeight);
    traverseLeftToRight(node->right, currentHeight + 1, maxHeightAfterRemoval, currentMaxHeight);
}
void traverseRightToLeft(struct TreeNode* node, int currentHeight, int* maxHeightAfterRemoval, int* currentMaxHeight) {
    if (node == NULL) {
        return;
    }

    // Update the maximum height if this node were removed
    maxHeightAfterRemoval[node->val] = fmax(maxHeightAfterRemoval[node->val], (*currentMaxHeight));

    // Update the current maximum height
    (*currentMaxHeight) = fmax(currentHeight, (*currentMaxHeight));

    // Traverse right subtree first, then left
    traverseRightToLeft(node->right, currentHeight + 1, maxHeightAfterRemoval, currentMaxHeight);
    traverseRightToLeft(node->left, currentHeight + 1, maxHeightAfterRemoval, currentMaxHeight);
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
int* treeQueries(struct TreeNode* root, int* queries, int queriesSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    // Array to store the maximum height of the tree after removing each node
    int* maxHeightAfterRemoval = (int*)malloc(100001 * sizeof(int));
    if (maxHeightAfterRemoval == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(maxHeightAfterRemoval, 0, (100001 * sizeof(int)));
    int currentMaxHeight = 0;
    traverseLeftToRight(root, 0, maxHeightAfterRemoval, &currentMaxHeight);
    currentMaxHeight = 0;
    traverseRightToLeft(root, 0, maxHeightAfterRemoval, &currentMaxHeight);

    pRetVal = (int*)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (queriesSize * sizeof(int)));

    int i;
    for (i = 0; i < queriesSize; ++i) {
        pRetVal[(*returnSize)++] = maxHeightAfterRemoval[queries[i]];
    }
    free(maxHeightAfterRemoval);
    maxHeightAfterRemoval = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int queries[MAX_SIZE];
        int queriesSize;
        int returnSize;
    } testCase[] = {
        {{1, 3, 4, 2, INT_MIN, 6, 5, INT_MIN, INT_MIN, INT_MAX, INT_MAX, INT_MIN, INT_MIN, INT_MIN, 7}, 15, {4}, 1, 0},
        {{5, 8, 9, 2, 1, 3, 7, 4, 6}, 9, {3, 2, 4, 8}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,3,4,2,null,6,5,null,null,null,null,null,7], queries = [4]
     *  Output: [2]
     *
     *  Input: root = [5,8,9,2,1,3,7,4,6], queries = [3,2,4,8]
     *  Output: [3,2,3,2]
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
        printf("], queries = [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].queries[j]);
        }
        printf("]\n");

        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        pAnswer = treeQueries(pRoot, testCase[i].queries, testCase[i].queriesSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
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
