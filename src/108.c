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
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    struct TreeNode* pRetVal = NULL;

    if (numsSize == 0) {
        return pRetVal;
    }

    int middle = numsSize / 2;
    pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = *(nums + middle);
    pRetVal->left = sortedArrayToBST(nums, middle);
    pRetVal->right = sortedArrayToBST(nums + middle + 1, numsSize - middle - 1);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{-10, -3, 0, 5, 9}, 5}, {{1, 3}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [-10,-3,0,5,9]
     *  Output: [0,-3,9,-10,null,5]
     *
     *  Input: nums = [1,3]
     *  Output: [3,1]
     */

    struct TreeNode* pAnswer = NULL;
    int height;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = sortedArrayToBST(testCase[i].nums, testCase[i].numsSize);
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
