#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void inOrder(struct TreeNode* pRoot, int* pTreeArray, int* pTreeNode) {
    if (pRoot == NULL) {
        return;
    }
    inOrder(pRoot->left, pTreeArray, pTreeNode);
    pTreeArray[(*pTreeNode)++] = pRoot->val;
    inOrder(pRoot->right, pTreeArray, pTreeNode);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool findTarget(struct TreeNode* root, int k) {
    bool retVal = false;

    // get sorted array by Binary Search Tree Inorder Traversal
#define MAX_NODE (10000)  // The number of nodes in the tree is in the range [1, 10^4]
    int treeArray[MAX_NODE];
    memset(treeArray, 0, sizeof(treeArray));
    int treeNode = 0;
    inOrder(root, treeArray, &treeNode);

    // move head and tail index of sorted array to check target sum
    int head = 0;
    int tail = treeNode - 1;
    while (head < tail) {
        if (treeArray[head] + treeArray[tail] == k) {
            retVal = true;
            break;
        } else if (treeArray[head] + treeArray[tail] > k) {
            --tail;
        } else if (treeArray[head] + treeArray[tail] < k) {
            ++head;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{5, 3, 6, 2, 4, INT_MIN, 7}, 7, 9}, {{5, 3, 6, 2, 4, INT_MIN, 7}, 7, 28}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [5,3,6,2,4,null,7], k = 9
     *  Output: true
     *
     *  Input: root = [5,3,6,2,4,null,7], k = 28
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
        printf("], k = %d\n", testCase[i].k);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        answer = findTarget(pRoot, testCase[i].k);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
