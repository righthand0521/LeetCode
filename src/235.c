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
#define RECURSION 1
#define ITERATIVE 1
/* Lowest Common Ancestor: https://en.wikipedia.org/wiki/Lowest_common_ancestor
 *  if root are bigger than p and q, then the Lowest Common Ancestor in root->left
 *  if root are smaller than p and q, then the Lowest Common Ancestor in root->right
 */
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (root == NULL) {
        return root;
    }

#if (RECURSION)
    if ((root->val > p->val) && (root->val > q->val)) {
        return lowestCommonAncestor(root->left, p, q);
    } else if ((root->val < p->val) && (root->val < q->val)) {
        return lowestCommonAncestor(root->right, p, q);
    }
#elif (ITERATIVE)
    while (root != NULL) {
        if ((root->val > p->val) && (root->val > q->val)) {
            root = root->left;
        } else if ((root->val < p->val) && (root->val < q->val)) {
            root = root->right;
        } else {
            break;
        }
    }
#endif

    return root;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int p;
        int q;
    } testCase[] = {{{6, 2, 8, 0, 4, 7, 9, INT_MIN, INT_MIN, 3, 5}, 11, 2, 8},
                    {{6, 2, 8, 0, 4, 7, 9, INT_MIN, INT_MIN, 3, 5}, 11, 2, 4},
                    {{2, 1}, 2, 2, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
     *  Output: 6
     *
     *  Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
     *  Output: 2
     *
     *  Input: root = [2,1], p = 2, q = 1
     *  Output: 2
     */

    struct TreeNode* pRoot = NULL;
    struct TreeNode* pTree = NULL;
    struct TreeNode* qTree = NULL;
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
        printf("], p = %d, q = %d\n", testCase[i].p, testCase[i].q);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);
        findSubTree(pRoot, testCase[i].p, &pTree);
        findSubTree(pRoot, testCase[i].q, &qTree);

        pAnswer = lowestCommonAncestor(pRoot, pTree, qTree);
        printf("Output: %d\n", pAnswer->val);

        printf("\n");

        pTree = NULL;
        qTree = NULL;
        pAnswer = NULL;
        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
