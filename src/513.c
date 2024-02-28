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
int findBottomLeftValue(struct TreeNode* root) {
    int retVal = 0;

#define MAX_QUEUE_SIZE (int)(1e4)  // The number of nodes in the tree is in the range [1, 10^4].
    struct TreeNode* bfsQueue[MAX_QUEUE_SIZE];
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;

    struct TreeNode* pCurrent = root;
    bfsQueue[bfsQueueTail++] = pCurrent;

    while (bfsQueueHead < bfsQueueTail) {
        pCurrent = bfsQueue[bfsQueueHead++];

        if (pCurrent->right != NULL) {
            bfsQueue[bfsQueueTail++] = pCurrent->right;
        }

        if (pCurrent->left != NULL) {
            bfsQueue[bfsQueueTail++] = pCurrent->left;
        }
    }
    retVal = pCurrent->val;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 1, 3}, 3}, {{1, 2, 3, 4, INT_MIN, 5, 6, INT_MIN, INT_MIN, INT_MAX, INT_MAX, 7}, 12}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [2,1,3]
     *  Output: 1
     *
     *  Input: root = [1,2,3,4,null,5,6,null,null,7]
     *  Output: 7
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
        printf("]\n");
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        answer = findBottomLeftValue(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
