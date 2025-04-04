#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

struct Pair {
    struct TreeNode* node;
    int depth;
};
struct Pair dfs(struct TreeNode* root) {
    struct Pair pRetVal = {NULL, 0};

    if (root == NULL) {
        return pRetVal;
    }

    struct Pair left = dfs(root->left);
    struct Pair right = dfs(root->right);
    if (left.depth > right.depth) {
        pRetVal = (struct Pair){left.node, left.depth + 1};
    } else if (left.depth < right.depth) {
        pRetVal = (struct Pair){right.node, right.depth + 1};
    } else {
        pRetVal = (struct Pair){root, left.depth + 1};
    }

    return pRetVal;
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* lcaDeepestLeaves(struct TreeNode* root) {
    struct TreeNode* pRetVal = NULL;

    pRetVal = dfs(root).node;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 5, 1, 6, 2, 0, 8, INT_MIN, INT_MIN, 7, 4}, 11}, {{1}, 1}, {{0, 1, 3, INT_MIN, 2}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [3,5,1,6,2,0,8,null,null,7,4]
     *  Output: [2,7,4]
     *
     *  Input: root = [1]
     *  Output: [1]
     *
     *  Input: root = [0,1,3,null,2]
     *  Output: [2]
     */

    struct TreeNode* pRoot = NULL;
    int height;
    struct TreeNode* pAnswer = NULL;
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

        pAnswer = lcaDeepestLeaves(pRoot);
        height = getTreeHeight(pAnswer);
        printf("Output: [");
        showTreeOutput(pAnswer, height);
        printf("]\n");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
