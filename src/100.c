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
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    bool retVal = false;

    if ((p == NULL) && (q == NULL)) {
        retVal = true;
        return retVal;
    } else if ((p == NULL) && (q != NULL)) {
        return retVal;
    } else if ((p != NULL) && (q == NULL)) {
        return retVal;
    }

    if (isSameTree(p->left, q->left) == false) {
        return retVal;
    }
    if (p->val != q->val) {
        return retVal;
    }
    if (isSameTree(p->right, q->right) == false) {
        return retVal;
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int p[MAX_SIZE];
        int pSize;
        int q[MAX_SIZE];
        int qSize;
    } testCase[] = {{{1, 2, 3}, 3, {1, 2, 3}, 3}, {{1, 2}, 2, {1, INT_MIN, 2}, 3}, {{1, 2, 1}, 3, {1, 1, 2}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: p = [1,2,3], q = [1,2,3]
     *  Output: true
     *
     *  Input: p = [1,2], q = [1,null,2]
     *  Output: false
     *
     *  Input: p = [1,2,1], q = [1,1,2]
     *  Output: false
     */

    struct TreeNode* pRoot = NULL;
    struct TreeNode* qRoot = NULL;
    bool answer = true;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: p = [");
        for (j = 0; j < testCase[i].pSize; ++j) {
            if (testCase[i].p[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
            } else if (testCase[i].p[j] == INT_MAX) {
                continue;
            } else {
                printf("%s%d", (j == 0 ? "" : ","), testCase[i].p[j]);
            }
        }
        printf("], q = [");
        for (j = 0; j < testCase[i].qSize; ++j) {
            if (testCase[i].q[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
            } else if (testCase[i].q[j] == INT_MAX) {
                continue;
            } else {
                printf("%s%d", (j == 0 ? "" : ","), testCase[i].q[j]);
            }
        }
        printf("]\n");
        pRoot = buildBinaryTree(testCase[i].p, testCase[i].pSize, 0);
        qRoot = buildBinaryTree(testCase[i].q, testCase[i].qSize, 0);

        answer = isSameTree(pRoot, qRoot);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        freeTreeNode(qRoot);
        qRoot = NULL;
    }

    return EXIT_SUCCESS;
}
