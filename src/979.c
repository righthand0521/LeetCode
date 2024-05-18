#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

int dfs(struct TreeNode* root, int* moves) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }
    int leftMoves = dfs(root->left, moves);
    int rightMoves = dfs(root->right, moves);
    (*moves) += (abs(leftMoves) + abs(rightMoves));
    retVal = (root->val - 1) + leftMoves + rightMoves;

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
int distributeCoins(struct TreeNode* root) {
    int retVal = 0;

    dfs(root, &retVal);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 0, 0}, 3}, {{0, 3, 0}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [3,0,0]
     *  Output: 2
     *
     *  Input: root = [0,3,0]
     *  Output: 3
     */

    struct TreeNode* pRoot = NULL;
    int answer;
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
        answer = distributeCoins(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
