#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

int height(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }
    retVal = -1;

    int left = height(root->left);
    if (left == -1) {
        return retVal;
    }

    int right = height(root->right);
    if (right == -1) {
        return retVal;
    }

    if (abs(left - right) > 1) {
        return retVal;
    }

    if (left > right) {
        retVal = left + 1;
    } else {
        retVal = right + 1;
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
bool isBalanced(struct TreeNode* root) {
    bool retVal = true;

    if (root == NULL) {
        return retVal;
    }
    retVal = (height(root) != -1);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 9, 20, INT_MIN, INT_MIN, 15, 7}, 7},
                    {{1, 2, 2, 3, 3, INT_MIN, INT_MIN, 4, 4}, 9},
                    {{}, 0},
                    {{2, 1, INT_MIN, 4}, 4},
                    {{1, 2, 3}, 3},
                    {{3, 4, 8, 5, 9, INT_MIN, 7, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 6}, 14}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [3,9,20,null,null,15,7]
     *  Output: true
     *
     *  Input: root = [1,2,2,3,3,null,null,4,4]
     *  Output: false
     *
     *  Input: root = []
     *  Output: true
     */

    struct TreeNode* pRoot = NULL;
    bool answer = true;
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

        answer = isBalanced(pRoot);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
