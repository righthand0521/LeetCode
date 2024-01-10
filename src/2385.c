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
#define MAX_NODE_ROW_SIZE (int)(1e5 + 4)  // 1 <= Node.val <= 10^5
#define MAX_NODE_COL_SIZE (3)             // TreeNode
void toUndirectedGraph(struct TreeNode* root, int** adjacency, int* adjacencyColSize) {
    if (root->left != NULL) {
        adjacency[root->val][adjacencyColSize[root->val]++] = root->left->val;
        adjacency[root->left->val][adjacencyColSize[root->left->val]++] = root->val;
        toUndirectedGraph(root->left, adjacency, adjacencyColSize);
    }

    if (root->right != NULL) {
        adjacency[root->val][adjacencyColSize[root->val]++] = root->right->val;
        adjacency[root->right->val][adjacencyColSize[root->right->val]++] = root->val;
        toUndirectedGraph(root->right, adjacency, adjacencyColSize);
    }
}
int amountOfTime(struct TreeNode* root, int start) {
    int retVal = 0;

    int i, j;

    //
    int* adjacencyColSize = (int*)malloc(MAX_NODE_ROW_SIZE * sizeof(int));
    if (adjacencyColSize == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(adjacencyColSize, 0, (MAX_NODE_ROW_SIZE * sizeof(int)));
    //
    int** adjacency = (int**)malloc(MAX_NODE_ROW_SIZE * sizeof(int*));
    if (adjacency == NULL) {
        perror("malloc");
        free(adjacencyColSize);
        adjacencyColSize = NULL;
        return retVal;
    }
    for (i = 0; i < MAX_NODE_ROW_SIZE; ++i) {
        adjacency[i] = (int*)malloc(MAX_NODE_COL_SIZE * sizeof(int));
        if (adjacency[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(adjacency[j]);
                adjacency[j] = NULL;
            }
            free(adjacency);
            adjacency = NULL;
            free(adjacencyColSize);
            adjacencyColSize = NULL;
            return retVal;
        }
        memset(adjacency[i], 0, (MAX_NODE_COL_SIZE * sizeof(int)));  // 1 <= Node.val <= 10^5
    }
    //
    toUndirectedGraph(root, adjacency, adjacencyColSize);
#if (0)
    for (i = 0; i < MAX_NODE_ROW_SIZE; ++i) {
        if (adjacencyColSize[i] != 0) {
            printf("%d: ", i);
            for (j = 0; j < adjacencyColSize[i]; ++j) {
                printf("%d ", adjacency[i][j]);
            }
            printf("\n");
        }
    }
#endif

    //
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    int bfsQueue[MAX_NODE_ROW_SIZE];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    bfsQueue[bfsQueueTail++] = start;
    //
    int visited[MAX_NODE_ROW_SIZE];
    memset(visited, 0, sizeof(visited));
    visited[start] = 1;
    //
    retVal = -1;
    int bfsQueueSize, leaf, neighbor;
    while (bfsQueueHead < bfsQueueTail) {
        bfsQueueSize = bfsQueueTail - bfsQueueHead;
        for (i = 0; i < bfsQueueSize; ++i) {
            leaf = bfsQueue[bfsQueueHead++];
            for (j = 0; j < adjacencyColSize[leaf]; ++j) {
                neighbor = adjacency[leaf][j];
                if (visited[neighbor] == 0) {
                    visited[neighbor] = 1;
                    bfsQueue[bfsQueueTail++] = neighbor;
                }
            }
        }
        ++retVal;
    }

    //
    for (i = 0; i < MAX_NODE_ROW_SIZE; ++i) {
        free(adjacency[i]);
        adjacency[i] = NULL;
    }
    free(adjacency);
    adjacency = NULL;
    free(adjacencyColSize);
    adjacencyColSize = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int start;
    } testCase[] = {{{1, 5, 3, INT_MIN, 4, 10, 6, INT_MAX, INT_MAX, 9, 2}, 11, 3}, {{1}, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,5,3,null,4,10,6,9,2], start = 3
     *  Output: 4
     *
     *  Input: root = [1], start = 1
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
        printf("], start = %d\n", testCase[i].start);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        answer = amountOfTime(pRoot, testCase[i].start);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
