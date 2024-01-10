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
struct TreeNode* constructFromPrePost(int* preorder, int preorderSize, int* postorder, int postorderSize) {
    struct TreeNode* pRetVal = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3000)
    struct testCaseType {
        int preorder[MAX_SIZE];
        int preorderSize;
        int postorder[MAX_SIZE];
        int postorderSize;
    } testCase[] = {{{1, 2, 4, 5, 3, 6, 7}, 7, {4, 5, 2, 6, 7, 3, 1}, 7}, {{1}, 1, {1}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
     *  Output: [1,2,3,4,5,6,7]
     *
     *  Input: preorder = [1], postorder = [1]
     *  Output: [1]
     */

    struct TreeNode* pAnswer = NULL;
    int height;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: preorder = [");
        for (j = 0; j < testCase[i].preorderSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].preorder[j]);
        }
        printf("], postorder = [");
        for (j = 0; j < testCase[i].postorderSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].postorder[j]);
        }
        printf("]\n");

        pAnswer = constructFromPrePost(testCase[i].preorder, testCase[i].preorderSize, testCase[i].postorder,
                                       testCase[i].postorderSize);
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
