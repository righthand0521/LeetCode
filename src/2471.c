#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

int compareLongLong(const void* n1, const void* n2) {
    // ascending order
    return (*(long long*)n1 > *(long long*)n2);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int minimumOperations(struct TreeNode* root) {
    int retVal = 0;

    const int MAX_NODE_SIZE = (1e5);  // The number of nodes in the tree is in the range [1, 10^5].
    const int SHIFT = 20;
    const int MASK = 0xFFFFF;

    // Process tree level by level using BFS
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    struct TreeNode* bfsQueue[MAX_NODE_SIZE];
    bfsQueue[bfsQueueTail++] = root;

    int tmp;
    int origPos;
    struct TreeNode* pTmp;
    long long* pNodes = NULL;
    int levelSize;
    while (bfsQueueTail > bfsQueueHead) {
        levelSize = bfsQueueTail - bfsQueueHead;
        pNodes = (long long*)calloc(levelSize, sizeof(long long));
        if (pNodes == NULL) {
            perror("calloc");
            return retVal;
        }

        // Store node values with encoded positions
        for (int i = 0; i < levelSize; i++) {
            pTmp = bfsQueue[bfsQueueHead++];

            // Encode value and index: high 20 bits = value, low 20 bits = index
            pNodes[i] = ((long long)(pTmp->val) << SHIFT) + i;

            if (pTmp->left != NULL) {
                bfsQueue[bfsQueueTail++] = pTmp->left;
            }
            if (pTmp->right != NULL) {
                bfsQueue[bfsQueueTail++] = pTmp->right;
            }
        }

        // Sort nodes by their values (high 20 bits)
        qsort(pNodes, levelSize, sizeof(long long), compareLongLong);

        // Count swaps needed to match indices with original positions
        for (int i = 0; i < levelSize; i++) {
            origPos = (int)(pNodes[i] & MASK);
            if (origPos != i) {
                // Swap nodes and decrement i to recheck current position
                tmp = pNodes[i];
                pNodes[i] = pNodes[origPos];
                pNodes[origPos] = tmp;

                retVal++;
                i--;
            }
        }

        //
        free(pNodes);
        pNodes = NULL;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 4, 3, 7, 6, 8, 5, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 9, INT_MIN, 10}, 14},
                    {{1, 3, 2, 7, 6, 5, 4}, 7},
                    {{1, 2, 3, 4, 5, 6}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,4,3,7,6,8,5,null,null,null,null,9,null,10]
     *  Output: 3
     *
     *  Input: root = [1,3,2,7,6,5,4]
     *  Output: 3
     *
     *  Input: root = [1,2,3,4,5,6]
     *  Output: 0
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

        answer = minimumOperations(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
