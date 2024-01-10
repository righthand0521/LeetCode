#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define DFS (1)
#define BFS (1)
#if (DFS)
int dfs(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    if ((root->left == NULL) && (root->right == NULL)) {
        retVal += 1;
        return retVal;
    }

    if (root->left == NULL) {
        retVal = 1 + dfs(root->right);
    } else if (root->right == NULL) {
        retVal = 1 + dfs(root->left);
    } else {
        retVal = 1 + fmin(dfs(root->left), dfs(root->right));
    }

    return retVal;
}
#elif (BFS)
#define MAX_QUEUE_SIZE (100000 * 2)  // The number of nodes in the tree is in the range [0, 10^5].
int bfs(struct TreeNode* root) {
    int retVal = 0;

    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    struct TreeNode* bfsQueue[MAX_QUEUE_SIZE];
    bfsQueue[bfsQueueTail] = root;
    ++bfsQueueTail;
    retVal = 1;

    int bfsQueueSize;
    struct TreeNode* pCurrent;
    int i;
    while (bfsQueueHead < bfsQueueTail) {
        bfsQueueSize = bfsQueueTail - bfsQueueHead;
        for (i = 0; i < bfsQueueSize; ++i) {
            pCurrent = bfsQueue[bfsQueueHead];
            ++bfsQueueHead;

            if ((pCurrent->left == NULL) && (pCurrent->right == NULL)) {
                return retVal;
            }

            if (pCurrent->left != NULL) {
                bfsQueue[bfsQueueTail] = pCurrent->left;
                ++bfsQueueTail;
            }
            if (pCurrent->right != NULL) {
                bfsQueue[bfsQueueTail] = pCurrent->right;
                ++bfsQueueTail;
            }
        }
        ++retVal;
    }

    return retVal;
}
#endif
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int minDepth(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

#if (DFS)
    printf("Depth-First Search\n\n");
    retVal = dfs(root);
#elif (BFS)
    printf("Breadth-First Search\n\n");
    retVal = bfs(root);
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 9, 20, INT_MIN, INT_MIN, 15, 7}, 7},
                    {{2,       INT_MIN, 3,       INT_MAX, INT_MAX, INT_MIN, 4,       INT_MAX, INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MIN, 5,       INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,
                      INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MIN, 6},
                     31}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [3,9,20,null,null,15,7]
     *  Output: 2
     *
     *  Input: root = [2,null,3,null,4,null,5,null,6]
     *  Output: 5
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

        answer = minDepth(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
