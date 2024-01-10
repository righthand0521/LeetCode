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
bool isCompleteTree(struct TreeNode* root) {
    bool retVal = false;

#define MAX_QUEUE_SIZE (100 * 2)  // The number of nodes in the tree is in the range [1, 100].
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    struct TreeNode* bfsQueue[MAX_QUEUE_SIZE];
    bfsQueue[bfsQueueTail] = root;
    ++bfsQueueTail;

    struct TreeNode* pCurrent;
    while (bfsQueueHead < bfsQueueTail) {
        pCurrent = bfsQueue[bfsQueueHead];
        ++bfsQueueHead;

        if (pCurrent == NULL) {
            retVal = true;
            continue;
        }

        if (retVal == true) {
            retVal = false;
            break;
        }

        bfsQueue[bfsQueueTail] = pCurrent->left;
        ++bfsQueueTail;
        bfsQueue[bfsQueueTail] = pCurrent->right;
        ++bfsQueueTail;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 4, 5, 6}, 6}, {{1, 2, 3, 4, 5, INT_MIN, 7}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,3,4,5,6]
     *  Output: true
     *
     *  Input: root = [1,2,3,4,5,null,7]
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

        answer = isCompleteTree(pRoot);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
