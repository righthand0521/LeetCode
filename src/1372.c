#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void dfs(struct TreeNode* root, bool dir, int len, int* retVal) {
    (*retVal) = fmax((*retVal), len);

    // bool dir: left is false, right is true.
    if (dir == false) {
        if (root->left) {
            dfs(root->left, true, len + 1, retVal);
        }
        if (root->right) {
            dfs(root->right, false, 1, retVal);
        }
    } else {
        if (root->right) {
            dfs(root->right, false, len + 1, retVal);
        }
        if (root->left) {
            dfs(root->left, true, 1, retVal);
        }
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
int longestZigZag(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    // bool dir: left is false, right is true.
    dfs(root, false, 0, &retVal);
    dfs(root, true, 0, &retVal);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {
        {{1,       INT_MIN, 1,       INT_MAX, INT_MAX, 1,       1,       INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MIN,
          INT_MIN, 1,       1,       INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
          INT_MAX, INT_MAX, INT_MAX, INT_MIN, 1,       INT_MIN, INT_MIN, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
          INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
          INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MIN, 1,       INT_MAX, INT_MAX, INT_MAX,
          INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
          INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
          INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
          INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MIN, 1},
         107},
        {{1,       1,       1,       INT_MIN, 1,       INT_MIN, INT_MIN, INT_MAX, INT_MAX, 1, 1,
          INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MIN, 1, INT_MAX,
          INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
         31},
        {{1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1,null,1]
     *  Output: 3
     *
     *  Input: root = [1,1,1,null,1,null,null,1,1,null,1]
     *  Output: 4
     *
     *  Input: root = [1]
     *  Output: 0
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
        answer = longestZigZag(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
