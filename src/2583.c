#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define MAX_NODES_SIZE (int)(1e5)  // The number of nodes in the tree is n. 2 <= n <= 10 ^ 5
int compareLongLongInteger(const void* n1, const void* n2) {
    // descending order
    return (*(long long*)n1 < *(long long*)n2);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
long long kthLargestLevelSum(struct TreeNode* root, int k) {
    long long retVal = -1;  // If there are fewer than k levels in the tree, return -1.

    int traversalIndex = 0;
    long long traversal[MAX_NODES_SIZE];
    memset(traversal, 0, sizeof(traversal));

    int queueHead = 0;
    int queueTail = 0;
    struct TreeNode* queue[MAX_NODES_SIZE];
    memset(queue, 0, sizeof(queue));
    queue[queueTail++] = root;

    struct TreeNode* node;
    int currentLevelSize;
    long long levelSum;
    while (queueHead < queueTail) {
        levelSum = 0;

        currentLevelSize = queueTail - queueHead;
        for (int i = 1; i <= currentLevelSize; ++i) {
            node = queue[queueHead++];
            levelSum += (long long)node->val;
            if (node->left != NULL) {
                queue[queueTail++] = node->left;
            }
            if (node->right != NULL) {
                queue[queueTail++] = node->right;
            }
        }

        traversal[traversalIndex++] = levelSum;
    }

    if (k <= traversalIndex) {
        qsort(traversal, traversalIndex, sizeof(long long), compareLongLongInteger);
        retVal = traversal[k - 1];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{5, 8, 9, 2, 1, 3, 7, 4, 6}, 9, 2}, {{1, 2, INT_MIN, 3}, 4, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [5,8,9,2,1,3,7,4,6], k = 2
     *  Output: 13
     *
     *  Input: root = [1,2,null,3], k = 1
     *  Output: 3
     */

    struct TreeNode* pRoot = NULL;
    long long answer = 0;
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

        answer = kthLargestLevelSum(pRoot, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
