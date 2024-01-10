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
#define DFS (0)
#define BFS (1)
#define MAX_TREE_NODE (int)(1e4)
void dfs(struct TreeNode* root, int level, int* sum, int* sumSize) {
    if (level == (*sumSize)) {
        sum[(*sumSize)++] = root->val;
    } else {
        sum[level] += root->val;
    }

    if (root->left != NULL) {
        dfs(root->left, level + 1, sum, sumSize);
    }
    if (root->right != NULL) {
        dfs(root->right, level + 1, sum, sumSize);
    }
}
int bfs(struct TreeNode* root) {
    int retVal = 0;

    int maxSum = INT_MIN;
    int level = 0;
    struct TreeNode* bfsQueue[MAX_TREE_NODE];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueHead++] = root;

    int bfsQueueCount;
    int sum;
    int i;
    struct TreeNode* node = NULL;
    while (bfsQueueHead > bfsQueueTail) {
        ++level;

        sum = 0;
        bfsQueueCount = bfsQueueHead - bfsQueueTail;
        for (i = 0; i < bfsQueueCount; ++i) {
            node = bfsQueue[bfsQueueTail];
            ++bfsQueueTail;
            sum += node->val;

            if (node->left != NULL) {
                bfsQueue[bfsQueueHead++] = node->left;
            }
            if (node->right != NULL) {
                bfsQueue[bfsQueueHead++] = node->right;
            }
        }

        if (maxSum < sum) {
            maxSum = sum;
            retVal = level;
        }
    }

    return retVal;
}
int maxLevelSum(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

#if (DFS)
    printf("Depth-First Search\n\n");

    int* sum = (int*)malloc(MAX_TREE_NODE * sizeof(int));
    if (sum == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(sum, 0, (MAX_TREE_NODE * sizeof(int)));
    int sumSize = 0;

    dfs(root, 0, sum, &sumSize);
    int maxSum = INT_MIN;
    int i;
    for (i = 0; i < sumSize; ++i) {
        if (maxSum < sum[i]) {
            maxSum = sum[i];
            retVal = i + 1;
        }
    }

    free(sum);
    sum = NULL;
#elif (BFS)
    printf("Breadth-First Search\n\n");

    retVal = bfs(root);
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 7, 0, 7, -8, INT_MIN, INT_MIN}, 7},
                    {{989, INT_MIN, 10250, 98693, -89388, INT_MIN, INT_MIN, INT_MIN, -32127}, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,7,0,7,-8,null,null]
     *  Output: 2
     *
     *  Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
     *  Output: 2
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

        answer = maxLevelSum(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
