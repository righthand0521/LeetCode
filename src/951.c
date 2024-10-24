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
bool flipEquiv(struct TreeNode* root1, struct TreeNode* root2) {
    bool retVal = false;

    if ((root1 == NULL) && (root2 == NULL)) {  // Both trees are empty
        retVal = true;
        return retVal;
    } else if (root1 == NULL || root2 == NULL) {  // Just one of the trees is empty
        return retVal;
    } else if (root1->val != root2->val) {  // Corresponding values differ
        return retVal;
    }

    // Check if corresponding subtrees are flip equivalent
    bool noSwap = flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right);
    // Check if opposite subtrees are flip equivalent
    bool swap = flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left);

    retVal = swap || noSwap;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int root1[MAX_SIZE];
        int root1Size;
        int root2[MAX_SIZE];
        int root2Size;
    } testCase[] = {{{1, 2, 3, 4, 5, 6, INT_MIN, INT_MIN, INT_MIN, 7, 8},
                     11,
                     {1, 3, 2, INT_MIN, 6, 4, 5, INT_MAX, INT_MAX, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 8, 7},
                     15},
                    {{}, 0, {}, 0},
                    {{}, 0, {1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
     *  Output: true
     *
     *  Input: root1 = [], root2 = []
     *  Output: true
     *
     *  Input: root1 = [], root2 = [1]
     *  Output: false
     */

    struct TreeNode* pRoot1 = NULL;
    struct TreeNode* pRoot2 = NULL;
    bool answer = true;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: root1 = [");
        for (j = 0; j < testCase[i].root1Size; ++j) {
            if (testCase[i].root1[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
            } else if (testCase[i].root1[j] == INT_MAX) {
                continue;
            } else {
                printf("%s%d", (j == 0 ? "" : ","), testCase[i].root1[j]);
            }
        }
        printf("], root2 = [");
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
        pRoot1 = buildBinaryTree(testCase[i].root1, testCase[i].root1Size, 0);
        pRoot2 = buildBinaryTree(testCase[i].root2, testCase[i].root2Size, 0);

        answer = flipEquiv(pRoot1, pRoot2);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        freeTreeNode(pRoot1);
        pRoot1 = NULL;
        freeTreeNode(pRoot2);
        pRoot2 = NULL;
    }

    return EXIT_SUCCESS;
}
