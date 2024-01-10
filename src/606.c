#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void inorder(struct TreeNode* root, char* pRetVal, int* returnSize) {
    if (root == NULL) {
        return;
    }

    snprintf(pRetVal + strlen(pRetVal), (*returnSize), "%d", root->val);

    if (root->left != NULL) {
        pRetVal[strlen(pRetVal)] = '(';
        inorder(root->left, pRetVal, returnSize);
        pRetVal[strlen(pRetVal)] = ')';
    }

    if (root->right != NULL) {
        if (root->left == NULL) {
            pRetVal[strlen(pRetVal)] = '(';
            pRetVal[strlen(pRetVal)] = ')';
        }

        pRetVal[strlen(pRetVal)] = '(';
        inorder(root->right, pRetVal, returnSize);
        pRetVal[strlen(pRetVal)] = ')';
    }
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
char* tree2str(struct TreeNode* root) {
    char* pRetVal = NULL;

    /* Constraints
     *  The number of nodes in the tree is in the range [1, 10^4].
     *  -1000 <= Node.val <= 1000
     */
    int returnSize = 1e5;
    pRetVal = (char*)calloc(returnSize, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    inorder(root, pRetVal, &returnSize);
    pRetVal[strlen(pRetVal)] = '\0';

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, 2, 3, 4}, 4}, {{1, 2, 3, INT_MIN, 4}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,3,4]
     *  Output: "1(2(4))(3)"
     *
     *  Input: root = [1,2,3,null,4]
     *  Output: "1(2()(4))(3)"
     */

    struct TreeNode* pRoot = NULL;
    char* pAnswer = NULL;
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

        pAnswer = tree2str(pRoot);
        printf("Output: %s\n", pAnswer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
