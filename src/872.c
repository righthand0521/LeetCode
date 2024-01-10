#include <stdbool.h>
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
void dfs(struct TreeNode* pRoot, int* pArr, int* pArrSize) {
    if (pRoot == NULL) {
        return;
    }

    if ((pRoot->left == NULL) && (pRoot->right == NULL)) {
        pArr[(*pArrSize)] = pRoot->val;
        ++(*pArrSize);
        return;
    }
    dfs(pRoot->left, pArr, pArrSize);
    dfs(pRoot->right, pArr, pArrSize);
}
bool leafSimilar(struct TreeNode* root1, struct TreeNode* root2) {
    bool retVal = false;

    // The number of nodes in each tree will be in the range [1, 200].
    int arr1[200];
    memset(arr1, 0, sizeof(arr1));
    int arr1Size = 0;
    dfs(root1, arr1, &arr1Size);

    // The number of nodes in each tree will be in the range [1, 200].
    int arr2[200];
    memset(arr2, 0, sizeof(arr2));
    int arr2Size = 0;
    dfs(root2, arr2, &arr2Size);

    // compare the number of leafs
    if (arr1Size != arr2Size) {
        return retVal;
    }

    // compare leaf's value
    int i;
    for (i = 0; i < arr1Size; ++i) {
        if (arr1[i] != arr2[i]) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int root1[MAX_SIZE];
        int root1Size;
        int root2[MAX_SIZE];
        int root2Size;

    } testCase[] = {{{3, 5, 1, 6, 2, 9, 8, INT_MIN, INT_MIN, 7, 4},
                     11,
                     {3, 5, 1, 6, 7, 4, 2, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 9, 8},
                     15},
                    {{1, 2, 3}, 3, {1, 3, 2}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
     *  Output: true
     *
     *  Input: root1 = [1,2,3], root2 = [1,3,2]
     *  Output: false
     */

    struct TreeNode* pRoot1 = NULL;
    struct TreeNode* pRoot2 = NULL;
    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: root = [");
        for (j = 0; j < testCase[i].root1Size; ++j) {
            if (testCase[i].root1[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
            } else if (testCase[i].root1[j] == INT_MAX) {
                continue;
            } else {
                printf("%s%d", (j == 0 ? "" : ","), testCase[i].root1[j]);
            }
        }
        printf("]");
        pRoot1 = buildBinaryTree(testCase[i].root1, testCase[i].root1Size, 0);
        printf(", root2 = [");
        for (j = 0; j < testCase[i].root2Size; ++j) {
            if (testCase[i].root2[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
            } else if (testCase[i].root2[j] == INT_MAX) {
                continue;
            } else {
                printf("%s%d", (j == 0 ? "" : ","), testCase[i].root2[j]);
            }
        }
        printf("]\n");
        pRoot2 = buildBinaryTree(testCase[i].root2, testCase[i].root2Size, 0);

        answer = leafSimilar(pRoot1, pRoot2);
        printf("Output: %s\n", answer == true ? "true" : "false");

        printf("\n");

        freeTreeNode(pRoot1);
        pRoot1 = NULL;
        freeTreeNode(pRoot2);
        pRoot2 = NULL;
    }

    return EXIT_SUCCESS;
}
