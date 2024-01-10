#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

// https://leetcode.cn/problems/all-possible-full-binary-trees/solutions/320161/c-di-gui-by-cjzswang5/
int calculateReturnSize(int n) {
    int retVal = 0;

    if ((n == 1) || (n == 3)) {
        retVal = 1;
        return retVal;
    }

    int i;
    for (i = 1; i < n; i += 2) {
        retVal += calculateReturnSize(i) * calculateReturnSize(n - i - 1);
    }

    return retVal;
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
struct TreeNode** allPossibleFBT(int n, int* returnSize) {
    struct TreeNode** pRetVal = NULL;

    if ((n % 2) == 0) {
        (*returnSize) = 0;
        return pRetVal;
    }

    if (n == 1) {
        (*returnSize) = 1;

        pRetVal = (struct TreeNode**)calloc(1, sizeof(struct TreeNode*));
        if (pRetVal == NULL) {
            perror("calloc");
            (*returnSize) = 0;
            return pRetVal;
        }
        pRetVal[0] = (struct TreeNode*)calloc(1, sizeof(struct TreeNode));
        if (pRetVal[0] == NULL) {
            perror("calloc");
            (*returnSize) = 0;
            return pRetVal;
        }
        pRetVal[0][0].val = 0;
        pRetVal[0][0].left = NULL;
        pRetVal[0][0].right = NULL;

        return pRetVal;
    }

    (*returnSize) = 0;
    pRetVal = (struct TreeNode**)calloc(calculateReturnSize(n), sizeof(struct TreeNode*));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    struct TreeNode** tmpLeft;
    int tmpLeftSize = 0;
    int tmpLeftSizeIdx = 0;
    struct TreeNode** tmpRight;
    int tmpRightSize = 0;
    int tmpRightSizeIdx = 0;
    int i;
    for (i = 1; i < n; i += 2) {
        tmpLeft = allPossibleFBT(i, &tmpLeftSize);
        tmpRight = allPossibleFBT(n - i - 1, &tmpRightSize);
        for (tmpLeftSizeIdx = 0; tmpLeftSizeIdx < tmpLeftSize; ++tmpLeftSizeIdx) {
            for (tmpRightSizeIdx = 0; tmpRightSizeIdx < tmpRightSize; ++tmpRightSizeIdx) {
                pRetVal[(*returnSize)] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                if (pRetVal[(*returnSize)] == NULL) {
                    perror("calloc");
                    (*returnSize) = 0;
                    return pRetVal;
                }
                pRetVal[(*returnSize)]->val = 0;
                pRetVal[(*returnSize)]->left = tmpLeft[tmpLeftSizeIdx];
                pRetVal[(*returnSize)]->right = tmpRight[tmpRightSizeIdx];
                ++(*returnSize);
            }
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int returnSize;
    } testCase[] = {{7, 0}, {3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 7
     *  Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],
     *  [0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
     *
     *  Input: n = 3
     *  Output: [[0,0,0]]
     */

    struct TreeNode** pAnswer = NULL;
    int height;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = allPossibleFBT(testCase[i].n, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            height = getTreeHeight(pAnswer[j]);
            showTreeOutput(pAnswer[j], height);
            printf("]");
        }
        printf("]\n");

        printf("\n");

        // freeTreeNode(pAnswer);
        // pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
