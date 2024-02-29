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
bool isEvenOddTree(struct TreeNode* root) {
    bool retVal = false;

#define MAX_QUEUE_SIZE (int)(1e5)  // The number of nodes in the tree is in the range [1, 10^5].
    struct TreeNode* bfsQueue[MAX_QUEUE_SIZE];
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueTail++] = root;

    int i;
    int level = 0;
    int previous, value;
    int bfsQueueSize = 0;
    struct TreeNode* pCurrent = NULL;
    while (bfsQueueHead < bfsQueueTail) {
        if (level % 2 == 0) {
            previous = INT_MIN;
        } else {
            previous = INT_MAX;
        }

        bfsQueueSize = bfsQueueTail - bfsQueueHead;
        for (i = 0; i < bfsQueueSize; ++i) {
            pCurrent = bfsQueue[bfsQueueHead++];
            value = pCurrent->val;
            if (level % 2 == 0) {
                if (value % 2 == 0) {
                    return retVal;
                } else if (value <= previous) {
                    return retVal;
                } else {
                    previous = value;
                }
            } else {
                if (value % 2 != 0) {
                    return retVal;
                } else if (value >= previous) {
                    return retVal;
                } else {
                    previous = value;
                }
            }

            if (pCurrent->left != NULL) {
                bfsQueue[bfsQueueTail++] = pCurrent->left;
            }
            if (pCurrent->right != NULL) {
                bfsQueue[bfsQueueTail++] = pCurrent->right;
            }
        }
        level++;
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 10, 4, 3, INT_MIN, 7, 9, 12, 8, INT_MAX, INT_MAX, 6, INT_MIN, INT_MIN, 2}, 15},
                    {{5, 4, 2, 3, 3, 7}, 6},
                    {{5, 9, 1, 3, 5, 7}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,10,4,3,null,7,9,12,8,6,null,null,2]
     *  Output: true
     *
     *  Input: root = [5,4,2,3,3,7]
     *  Output: false
     *
     *  Input: root = [5,9,1,3,5,7]
     *  Output: false
     */

    struct TreeNode* pRoot = NULL;
    bool answer;
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

        answer = isEvenOddTree(pRoot);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
