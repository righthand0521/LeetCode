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
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    struct TreeNode* pRetVal = root;

    struct TreeNode* current = root;
    struct TreeNode* currentParent = NULL;
    while ((current != NULL) && (current->val != key)) {
        currentParent = current;
        if (current->val > key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        return pRetVal;
    }

    struct TreeNode* successor = NULL;
    struct TreeNode* successorParent = NULL;
    if ((current->left == NULL) && (current->right == NULL)) {
        current = NULL;
    } else if (current->right == NULL) {
        current = current->left;
    } else if (current->left == NULL) {
        current = current->right;
    } else {
        successor = current->right;
        successorParent = current;
        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }

        if (successorParent->val == current->val) {
            successorParent->right = successor->right;
        } else {
            successorParent->left = successor->right;
        }
        successor->right = current->right;
        successor->left = current->left;
        current = successor;
    }

    if (currentParent == NULL) {
        pRetVal = current;
        return pRetVal;
    }

    struct TreeNode* pFree = NULL;
    if ((currentParent->left != NULL) && (currentParent->left->val == key)) {
        pFree = currentParent->left;
        currentParent->left = current;
    } else {
        pFree = currentParent->right;
        currentParent->right = current;
    }
    free(pFree);
    pFree = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int key;
    } testCase[] = {{{5, 3, 6, 2, 4, INT_MIN, 7}, 7, 3}, {{5, 3, 6, 2, 4, INT_MIN, 7}, 7, 0}, {{}, 0, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [5,3,6,2,4,null,7], key = 3
     *  Output: [5,4,6,2,null,null,7]
     *
     *  Input: root = [5,3,6,2,4,null,7], key = 0
     *  Output: [5,3,6,2,4,null,7]
     *
     *  Input: root = [], key = 0
     *  Output: []
     */

    struct TreeNode* pRoot = NULL;
    int height;
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
        printf("], key = %d\n", testCase[i].key);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        pAnswer = deleteNode(pRoot, testCase[i].key);
        height = getTreeHeight(pAnswer);
        printf("Output: [");
        showTreeOutput(pAnswer, height);
        printf("]\n");

        printf("\n");

        freeTreeNode(pAnswer);
        pAnswer = NULL;
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
