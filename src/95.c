#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

struct TreeNode** buildTree(int start, int end, int* returnSize) {
    struct TreeNode** pRetVal = NULL;

    (*returnSize) = 0;

    if (start > end) {
        (*returnSize) = 1;
        pRetVal = malloc(sizeof(struct TreeNode*));
        pRetVal[0] = NULL;

        return pRetVal;
    }

    struct TreeNode** allTrees = (struct TreeNode**)malloc(0);
    struct TreeNode** leftTrees;
    int left;
    int leftTreesSize;
    struct TreeNode** rightTrees;
    int right;
    int rightTreesSize;
    struct TreeNode* pCurrTree;
    int i;
    for (i = start; i <= end; i++) {
        leftTrees = buildTree(start, i - 1, &leftTreesSize);
        rightTrees = buildTree(i + 1, end, &rightTreesSize);

        for (left = 0; left < leftTreesSize; left++) {
            for (right = 0; right < rightTreesSize; right++) {
                pCurrTree = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                pCurrTree->val = i;
                pCurrTree->left = leftTrees[left];
                pCurrTree->right = rightTrees[right];

                (*returnSize)++;
                allTrees = (struct TreeNode**)realloc(allTrees, sizeof(struct TreeNode*) * (*returnSize));
                allTrees[(*returnSize) - 1] = pCurrTree;
            }
        }
        free(rightTrees);
        rightTrees = NULL;
        free(leftTrees);
        leftTrees = NULL;
    }
    return allTrees;
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** generateTrees(int n, int* returnSize) {
    struct TreeNode** pRetVal = NULL;

    (*returnSize) = 0;

    if (n == 0) {
        return pRetVal;
    }
    pRetVal = buildTree(1, n, returnSize);

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int returnSize;
    } testCase[] = {{3, 0}, {1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3
     *  Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
     *
     *  Input: n = 1
     *  Output: [[1]]
     */

    struct TreeNode** pAnswer = NULL;
    int height;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = generateTrees(testCase[i].n, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            height = getTreeHeight(pAnswer[j]);
            showTreeOutput(pAnswer[j], height);
            printf("]");
            freeTreeNode(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        printf("]\n");

        printf("\n");
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
