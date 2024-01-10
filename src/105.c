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
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    struct TreeNode* pRetVal = NULL;

    if (preorderSize == 0) {
        return pRetVal;
    }

    int preorderIndex = preorderSize;
    int inorderIndex = 0;
    struct TreeNode* stack[preorderSize];
    int stackTop = -1;

    /* Example
     *      (3)        v  pre: 3  9 20 15  7
     *   (9)   (20)    v   in: 9  3 15 20  7
     *      (15)  (7)    post: 9 15  7 20  3
     */
    pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = preorder[0];
    pRetVal->left = NULL;
    pRetVal->right = NULL;
    stack[++stackTop] = pRetVal;

    int preorderVal;
    struct TreeNode* pTop;
    int i;
    for (i = 1; i < preorderIndex; ++i) {
        preorderVal = preorder[i];
        pTop = stack[stackTop];
        if (pTop->val != inorder[inorderIndex]) {
            pTop->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            if (pTop->left == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pTop->left->val = preorderVal;
            pTop->left->left = NULL;
            pTop->left->right = NULL;
            stack[++stackTop] = pTop->left;
        } else {
            while ((stackTop != -1) && (stack[stackTop]->val == inorder[inorderIndex])) {
                pTop = stack[stackTop--];
                ++inorderIndex;
            }
            pTop->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            if (pTop->right == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pTop->right->val = preorderVal;
            pTop->right->left = NULL;
            pTop->right->right = NULL;
            stack[++stackTop] = pTop->right;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3000)
    struct testCaseType {
        int preorder[MAX_SIZE];
        int preorderSize;
        int inorder[MAX_SIZE];
        int inorderSize;
    } testCase[] = {{{3, 9, 20, 15, 7}, 5, {9, 3, 15, 20, 7}, 5}, {{-1}, 1, {-1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
     *  Output: [3,9,20,null,null,15,7]
     *
     *  Input: preorder = [-1], inorder = [-1]
     *  Output: [-1]
     */

    struct TreeNode* pAnswer = NULL;
    int height;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: preorder = [");
        for (j = 0; j < testCase[i].preorderSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].preorder[j]);
        }
        printf("], inorder = [");
        for (j = 0; j < testCase[i].inorderSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].inorder[j]);
        }
        printf("]\n");

        pAnswer =
            buildTree(testCase[i].preorder, testCase[i].preorderSize, testCase[i].inorder, testCase[i].inorderSize);
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
