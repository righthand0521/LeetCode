#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define DFS (0)
#define BFS (1)
#define MAX_TREE_NODE (int)(1e4)  // The number of nodes in the tree will be in the range [0, 10^4].
void dfs(struct TreeNode* root, int level, int* answer, int* answerSize) {
    if (root == NULL) {
        return;
    }

    if (level == (*answerSize)) {
        answer[(*answerSize)++] = root->val;
    } else {
        answer[level] = fmax(answer[level], root->val);
    }

    dfs(root->left, level + 1, answer, answerSize);
    dfs(root->right, level + 1, answer, answerSize);
}
void bfs(struct TreeNode* root, int* answer, int* answerSize) {
    struct TreeNode* bfsQueue[MAX_TREE_NODE];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueHead++] = root;

    int maxValue;
    int bfsQueueCount;
    int i;
    struct TreeNode* node = NULL;
    while (bfsQueueHead > bfsQueueTail) {
        maxValue = INT_MIN;  // -2^31 <= Node.val <= 2^31 - 1

        bfsQueueCount = bfsQueueHead - bfsQueueTail;
        for (i = 0; i < bfsQueueCount; ++i) {
            node = bfsQueue[bfsQueueTail];
            ++bfsQueueTail;

            maxValue = fmax(maxValue, node->val);

            if (node->left != NULL) {
                bfsQueue[bfsQueueHead++] = node->left;
            }
            if (node->right != NULL) {
                bfsQueue[bfsQueueHead++] = node->right;
            }
        }

        answer[(*answerSize)++] = maxValue;
    }
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* largestValues(struct TreeNode* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    if (root == NULL) {
        return pRetVal;
    }

    pRetVal = (int*)malloc(MAX_TREE_NODE * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (MAX_TREE_NODE * sizeof(int)));

#if (DFS)
    printf("Depth-First Search\n\n");
    dfs(root, 0, pRetVal, returnSize);
#elif (BFS)
    printf("Breadth-First Search\n\n");
    bfs(root, pRetVal, returnSize);
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, 3, 2, 5, 3, INT_MAX, 9}, 7, 0}, {{1, 2, 3}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,3,2,5,3,null,9]
     *  Output: [1,3,9]
     *
     *  Input: root = [1,2,3]
     *  Output: [1,3]
     */

    struct TreeNode* pRoot = NULL;
    int* pAnswer = NULL;
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

        pAnswer = largestValues(pRoot, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
