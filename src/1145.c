#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

int nodeCount(struct TreeNode* pRoot, int* leftCount, int* rightCount, int nodeValue) {
    if (pRoot == NULL) {
        return 0;
    }

    int left = nodeCount(pRoot->left, leftCount, rightCount, nodeValue);
    int right = nodeCount(pRoot->right, leftCount, rightCount, nodeValue);
    if (pRoot->val == nodeValue) {
        (*leftCount) = left;
        (*rightCount) = right;
    }

    return (left + right + 1);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool btreeGameWinningMove(struct TreeNode* root, int n, int x) {
    bool retVal = false;

    int left = 0;
    int right = 0;
    nodeCount(root, &left, &right, x);

    if (left > (n / 2)) {
        retVal = true;
    } else if (right > (n / 2)) {
        retVal = true;
    } else if ((n - 1 - left - right) > (n / 2)) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int n;
        int x;
    } testCase[] = {{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, 11, 11, 3}, {{1, 2, 3}, 3, 3, 1}, {{1, 2, 3, 4, 5}, 5, 5, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
     *  Output: true
     *
     *  Input: root = [1,2,3], n = 3, x = 1
     *  Output: false
     */

    struct TreeNode* pRoot = NULL;
    bool answer = false;
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
        printf("], n = %d, x = %d\n", testCase[i].n, testCase[i].x);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        answer = btreeGameWinningMove(pRoot, testCase[i].n, testCase[i].x);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
