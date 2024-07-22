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
void flatten(struct TreeNode* root) {
    struct TreeNode* pNext = NULL;
    struct TreeNode* pPrevious = NULL;
    struct TreeNode* pCurrent = root;
    while (pCurrent != NULL) {
        if (pCurrent->left != NULL) {
            pNext = pCurrent->left;
            pPrevious = pCurrent->left;
            while (pPrevious->right != NULL) {
                pPrevious = pPrevious->right;
            }
            pPrevious->right = pCurrent->right;
            pCurrent->left = NULL;
            pCurrent->right = pNext;
        }
        pCurrent = pCurrent->right;
    }
}

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 5, 3, 4, INT_MIN, 6}, 7}, {{}, 0}, {{0}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,5,3,4,null,6]
     *  Output: [1,null,2,null,3,null,4,null,5,null,6]
     *
     *  Input: root = []
     *  Output: []
     *
     *  Input: root = [0]
     *  Output: [0]
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

        flatten(pRoot);
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
