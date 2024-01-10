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
bool isIdentical(struct TreeNode* pRoot1, struct TreeNode* pRoot2) {
    /* If any of the nodes is null, then both must be null.
     *
     *  isIdentical    | pRoot2 == NULL | pRoot2 != NULL
     *---------------------------------------------------
     *  pRoot1 == NULL |      true      |      false
     *  pRoot1 != NULL |      false     |      recursive
     *
     * If both nodes are non-empty, then they are identical only if
     *  1. Their values are equal
     *  2. Their left subtrees are identical
     *  3. Their right subtrees are identical
     */

    if ((pRoot1 == NULL) && (pRoot2 == NULL)) {
        return true;
    }

    if (((pRoot1 != NULL) && (pRoot2 == NULL)) || ((pRoot1 == NULL) && (pRoot2 != NULL))) {
        return false;
    }

    if (pRoot1->val != pRoot2->val) {
        return false;
    }

    if (isIdentical(pRoot1->left, pRoot2->left) == false) {
        return false;
    }

    if (isIdentical(pRoot1->right, pRoot2->right) == false) {
        return false;
    }

    return true;
}
bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot) {
    if (root == NULL) {
        return false;
    }

    if (isIdentical(root, subRoot) == true) {
        return true;
    }

    if (isSubtree(root->left, subRoot) == true) {
        return true;
    }

    if (isSubtree(root->right, subRoot) == true) {
        return true;
    }

    return false;
}

int main(int argc, char** argv) {
#define MAX_TREE (2000)
#define MAX_SUBTREE (1000)
    struct testCaseType {
        int tree[MAX_TREE];
        int treeSize;
        int subtree[MAX_SUBTREE];
        int subtreeSize;
    } testCase[] = {{{3, 4, 5, 1, 2}, 5, {4, 1, 2}, 3},
                    {{3, 4, 5, 1, 2, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 0}, 10, {4, 1, 2}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [3,4,5,1,2], subRoot = [4,1,2]
     *  Output: true
     *
     *  Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
     *  Output: false
     */

    struct TreeNode* pRoot = NULL;
    struct TreeNode* pSubRoot = NULL;
    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: root = [");
        for (j = 0; j < testCase[i].treeSize; ++j) {
            if (testCase[i].tree[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
            } else if (testCase[i].tree[j] == INT_MAX) {
                continue;
            } else {
                printf("%s%d", (j == 0 ? "" : ","), testCase[i].tree[j]);
            }
        }
        printf("]");
        pRoot = buildBinaryTree(testCase[i].tree, testCase[i].treeSize, 0);
        printf(", subRoot = [");
        for (j = 0; j < testCase[i].subtreeSize; ++j) {
            if (testCase[i].subtree[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
            } else if (testCase[i].subtree[j] == INT_MAX) {
                continue;
            } else {
                printf("%s%d", (j == 0 ? "" : ","), testCase[i].subtree[j]);
            }
        }
        printf("]\n");
        pSubRoot = buildBinaryTree(testCase[i].subtree, testCase[i].subtreeSize, 0);

        answer = isSubtree(pRoot, pSubRoot);
        printf("Output: %s\n", answer == true ? "true" : "false");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        freeTreeNode(pSubRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
