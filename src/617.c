#include <stdbool.h>
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
struct TreeNode* mergeTrees(struct TreeNode* root1, struct TreeNode* root2) {
    struct TreeNode* pRetVal = NULL;

    if ((root1 == NULL) && (root2 == NULL)) {
        return pRetVal;
    } else if ((root1 != NULL) && (root2 == NULL)) {
        pRetVal = root1;
        return pRetVal;
    } else if ((root1 == NULL) && (root2 != NULL)) {
        pRetVal = root2;
        return pRetVal;
    }

    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);
    root1->val += root2->val;
    pRetVal = root1;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        int root1[MAX_SIZE];
        int root1Size;
        int root2[MAX_SIZE];
        int root2Size;
    } testCase[] = {{{1, 3, 2, 5}, 4, {2, 1, 3, INT_MIN, 4, INT_MIN, 7}, 7}, {{1}, 1, {1, 2}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
     *  Output: [3,4,5,5,4,null,7]
     *
     *  Input: root1 = [1], root2 = [1,2]
     *  Output: [2,2]
     */

    struct TreeNode* pRoot1 = NULL;
    struct TreeNode* pRoot2 = NULL;
    struct TreeNode* pAnswer = NULL;
    int height;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: root = [");
        for (j = 0; j < testCase[i].root1Size; ++j) {
            if (testCase[i].root1[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
            } else if (testCase[i].root1[j] == INT_MAX) {
                continue;
            } else {
                printf("%s%d", (j == 0 ? "" : ","), testCase[i].root1[j]);
            }
        }
        printf("]");
        pRoot1 = buildBinaryTree(testCase[i].root1, testCase[i].root1Size, 0);
        printf(", root2 = [");
        for (j = 0; j < testCase[i].root2Size; ++j) {
            if (testCase[i].root2[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
            } else if (testCase[i].root2[j] == INT_MAX) {
                continue;
            } else {
                printf("%s%d", (j == 0 ? "" : ","), testCase[i].root2[j]);
            }
        }
        printf("]\n");
        pRoot2 = buildBinaryTree(testCase[i].root2, testCase[i].root2Size, 0);

        pAnswer = mergeTrees(pRoot1, pRoot2);
        height = getTreeHeight(pAnswer);
        printf("Output: [");
        showTreeOutput(pAnswer, height);
        printf("]\n");

        printf("\n");

        freeTreeNode(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
