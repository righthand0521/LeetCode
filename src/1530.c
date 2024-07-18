#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

// https://leetcode.cn/problems/number-of-good-leaf-nodes-pairs/solutions/2526545/po-su-de-si-lu-ji-zhi-de-bao-li-by-xun-j-iod9/
void lookChild(struct TreeNode* root, int subtree[], int* subtreeIndex, int deep) {
    if (root == NULL) {
        return;
    } else if ((root->left == NULL) && (root->right == NULL)) {
        subtree[(*subtreeIndex)++] = deep;
        return;
    }

    lookChild(root->left, subtree, subtreeIndex, deep + 1);
    lookChild(root->right, subtree, subtreeIndex, deep + 1);
}
void dfs(struct TreeNode* root, int distance, int* ans) {
    if (root == NULL) {
        return;
    } else if ((root->left == NULL) && (root->right == NULL)) {
        return;
    }

    int maxNodes = 1024;  // The number of nodes in the tree is in the range [1, 2^10].

    int leftIndex = 0;
    int left[maxNodes];
    memset(left, 0, sizeof(left));
    lookChild(root->left, left, &leftIndex, 1);

    int rightIndex = 0;
    int right[maxNodes];
    memset(right, 0, sizeof(right));
    lookChild(root->right, right, &rightIndex, 1);

    int i, j;
    for (i = 0; i < leftIndex; i++) {
        for (j = 0; j < rightIndex; j++) {
            if (left[i] + right[j] <= distance) {
                (*ans)++;
            }
        }
    }
    dfs(root->left, distance, ans);
    dfs(root->right, distance, ans);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int countPairs(struct TreeNode* root, int distance) {
    int retVal = 0;

    dfs(root, distance, &retVal);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1024)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int distance;
    } testCase[] = {
        {{1, 2, 3, INT_MIN, 4}, 5, 3},
        {{1, 2, 3, 4, 5, 6, 7}, 7, 3},
        {{7, 1, 4, 6, INT_MIN, 5, 3, INT_MIN, INT_MIN, INT_MAX, INT_MAX, INT_MIN, INT_MIN, INT_MIN, 2}, 15, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,3,null,4], distance = 3
     *  Output: 1
     *
     *  Input: root = [1,2,3,4,5,6,7], distance = 3
     *  Output: 2
     *
     *  Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2], distance = 3
     *  Output: 1
     */

    struct TreeNode* pRoot = NULL;
    int answer = 0;
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
        printf("], distance = %d\n", testCase[i].distance);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        answer = countPairs(pRoot, testCase[i].distance);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
