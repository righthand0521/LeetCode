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
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    struct TreeNode* pRetVal = NULL;

    if (postorderSize == 0) {
        return pRetVal;
    }

    int postorderIndex = postorderSize - 1;
    int inorderIndex = inorderSize - 1;
    struct TreeNode* stack[postorderSize];
    int stackTop = -1;

    /* Example
     *      (3)           pre: 3  9 20 15  7
     *   (9)   (20)    v   in: 9  3 15 20  7
     *      (15)  (7)  v post: 9 15  7 20  3
     */
    pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = postorder[postorderIndex];
    pRetVal->left = NULL;
    pRetVal->right = NULL;
    stack[++stackTop] = pRetVal;

    int postorderVal;
    struct TreeNode* pTop;
    int i;
    for (i = postorderIndex - 1; i >= 0; --i) {
        postorderVal = postorder[i];
        pTop = stack[stackTop];
        if (pTop->val != inorder[inorderIndex]) {
            pTop->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            if (pTop->right == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pTop->right->val = postorderVal;
            pTop->right->left = NULL;
            pTop->right->right = NULL;
            stack[++stackTop] = pTop->right;
        } else {
            while ((stackTop != -1) && (stack[stackTop]->val == inorder[inorderIndex])) {
                pTop = stack[stackTop--];
                --inorderIndex;
            }
            pTop->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            if (pTop->left == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pTop->left->val = postorderVal;
            pTop->left->left = NULL;
            pTop->left->right = NULL;
            stack[++stackTop] = pTop->left;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3000)
    struct testCaseType {
        int inorder[MAX_SIZE];
        int inorderSize;
        int postorder[MAX_SIZE];
        int postorderSize;
    } testCase[] = {{{9, 3, 15, 20, 7}, 5, {9, 15, 7, 20, 3}, 5}, {{-1}, 1, {-1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
     *  Output: [3,9,20,null,null,15,7]
     *
     *  Input: inorder = [-1], postorder = [-1]
     *  Output: [-1]
     */

    struct TreeNode* pAnswer = NULL;
    int height;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: inorder = [");
        for (j = 0; j < testCase[i].inorderSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].inorder[j]);
        }
        printf("], postorder = [");
        for (j = 0; j < testCase[i].postorderSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].postorder[j]);
        }
        printf("]\n");

        pAnswer =
            buildTree(testCase[i].inorder, testCase[i].inorderSize, testCase[i].postorder, testCase[i].postorderSize);
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
