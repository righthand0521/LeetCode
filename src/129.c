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
#define DEPTH_FIRST_SEARCH (1)
#define BREADTH_FIRST_SEARCH (1)
#if (DEPTH_FIRST_SEARCH)
int dfs(struct TreeNode* pRoot, int sum) {
    int retVal = 0;

    if (pRoot == NULL) {
        return retVal;
    }

    retVal = 10 * sum + pRoot->val;
    if ((pRoot->left == NULL) && (pRoot->right == NULL)) {
        return retVal;
    }
    retVal = dfs(pRoot->left, retVal) + dfs(pRoot->right, retVal);

    return retVal;
}
#elif (BREADTH_FIRST_SEARCH)
#define MAX_QUEUE_SIZE (1000 * 2)  // The number of nodes in the tree is in the range [1, 1000].
int bfs(struct TreeNode* pRoot) {
    int retVal = 0;

    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    struct TreeNode* bfsNodeQueue[MAX_QUEUE_SIZE];
    int bfsSumQueue[MAX_QUEUE_SIZE];
    bfsNodeQueue[bfsQueueTail] = pRoot;
    bfsSumQueue[bfsQueueTail] = pRoot->val;
    ++bfsQueueTail;

    struct TreeNode* pCurrent;
    int sum;
    while (bfsQueueHead < bfsQueueTail) {
        pCurrent = bfsNodeQueue[bfsQueueHead];
        sum = bfsSumQueue[bfsQueueHead];
        ++bfsQueueHead;

        if ((pCurrent->left == NULL) && (pCurrent->right == NULL)) {
            retVal += sum;
            continue;
        }

        if (pCurrent->left != NULL) {
            bfsNodeQueue[bfsQueueTail] = pCurrent->left;
            bfsSumQueue[bfsQueueTail] = sum * 10 + pCurrent->left->val;
            ++bfsQueueTail;
        }
        if (pCurrent->right != NULL) {
            bfsNodeQueue[bfsQueueTail] = pCurrent->right;
            bfsSumQueue[bfsQueueTail] = sum * 10 + pCurrent->right->val;
            ++bfsQueueTail;
        }
    }

    return retVal;
}
#endif
int sumNumbers(struct TreeNode* root) {
    int retVal = 0;

#if (DEPTH_FIRST_SEARCH)
    printf("DEPTH_FIRST_SEARCH\n");
    retVal = dfs(root, 0);
#elif (BREADTH_FIRST_SEARCH)
    printf("BREADTH_FIRST_SEARCH\n");
    retVal = bfs(root);
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3}, 3}, {{4, 9, 0, 5, 1}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,3]
     *  Output: 25
     *
     *  Input: root = [4,9,0,5,1]
     *  Output: 1026
     */

    struct TreeNode* pRoot = NULL;
    int answer;
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

        answer = sumNumbers(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
