#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define MAX_NODE (500 + 4)  // The number of nodes in the tree is in the range [1, 500].
struct GraphNode {
    int adjacent[4];  // the adjacent of binary tree would not exceed 3
    int adjacentSize;
};
void binaryTreeToGraph(struct TreeNode* root, struct GraphNode* graph) {
    if (root == NULL) {
        return;
    }

    int graphIdx, adjacentIdx;
    if (root->left != NULL) {
        graphIdx = root->val;
        adjacentIdx = graph[graphIdx].adjacentSize;
        graph[graphIdx].adjacent[adjacentIdx] = root->left->val;
        graph[graphIdx].adjacentSize += 1;

        graphIdx = root->left->val;
        adjacentIdx = graph[graphIdx].adjacentSize;
        graph[graphIdx].adjacent[adjacentIdx] = root->val;
        graph[graphIdx].adjacentSize += 1;

        binaryTreeToGraph(root->left, graph);
    }
    if (root->right != NULL) {
        graphIdx = root->val;
        adjacentIdx = graph[graphIdx].adjacentSize;
        graph[graphIdx].adjacent[adjacentIdx] = root->right->val;
        graph[graphIdx].adjacentSize += 1;

        graphIdx = root->right->val;
        adjacentIdx = graph[graphIdx].adjacentSize;
        graph[graphIdx].adjacent[adjacentIdx] = root->val;
        graph[graphIdx].adjacentSize += 1;

        binaryTreeToGraph(root->right, graph);
    }
}
#define MAX_QUEUE_SIZE ((MAX_NODE)*2)
struct QueueNode {
    int vertex;
    int distance;
};
int* bfs(struct TreeNode* root, struct TreeNode* target, int k, int* returnSize, struct GraphNode* graph) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc((MAX_NODE) * sizeof(int));  // The number of nodes in the tree is in the range [1, 500].
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((MAX_NODE) * sizeof(int)));

    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    struct QueueNode bfsQueue[MAX_QUEUE_SIZE];
    bfsQueue[bfsQueueTail].vertex = target->val;
    bfsQueue[bfsQueueTail].distance = 0;
    ++bfsQueueTail;

    // The number of nodes in the tree is in the range [1, 500].
    // 0 <= Node.val <= 500; All the values Node.val are unique.
    bool visited[(MAX_NODE)];
    memset(visited, false, sizeof(visited));
    visited[target->val] = true;

    int neighbor;
    int vertex, distance;
    int i;
    while (bfsQueueHead < bfsQueueTail) {
        vertex = bfsQueue[bfsQueueHead].vertex;
        distance = bfsQueue[bfsQueueHead].distance;
        ++bfsQueueHead;

        if (distance == k) {
            pRetVal[(*returnSize)++] = vertex;
        }

        for (i = 0; i < graph[vertex].adjacentSize; ++i) {
            neighbor = graph[vertex].adjacent[i];
            if (visited[neighbor] == true) {
                continue;
            }
            bfsQueue[bfsQueueTail].vertex = neighbor;
            bfsQueue[bfsQueueTail].distance = distance + 1;
            ++bfsQueueTail;
            visited[neighbor] = true;
        }
    }

    return pRetVal;
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
int* distanceK(struct TreeNode* root, struct TreeNode* target, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    // 0 <= Node.val <= 500; All the values Node.val are unique.
    struct GraphNode* pGraph = (struct GraphNode*)malloc((MAX_NODE) * sizeof(struct GraphNode));
    if (pGraph == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pGraph, 0, ((MAX_NODE) * sizeof(struct GraphNode)));
    binaryTreeToGraph(root, pGraph);
#if (0)
    for (int i = 0; i < (MAX_NODE); ++i) {
        printf("%d: [", i);
        for (int j = 0; j < pGraph[i].adjacentSize; ++j) {
            printf("%d ", pGraph[i].adjacent[j]);
        }
        printf("]\n");
    }
#endif

    pRetVal = bfs(root, target, k, returnSize, pGraph);

    //
    free(pGraph);
    pGraph = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int target;
        int k;
        int returnSize;
    } testCase[] = {{{3, 5, 1, 6, 2, 0, 8, INT_MIN, INT_MIN, 7, 4}, 11, 5, 2, 0}, {{1}, 1, 1, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
     *  Output: [7,4,1]
     *
     *  Input: root = [1], target = 1, k = 3
     *  Output: []
     */

    struct TreeNode* pRoot = NULL;
    struct TreeNode* pTarget = NULL;
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
        printf("], target = %d, k = %d\n", testCase[i].target, testCase[i].k);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        if (testCase[i].target == 5) {
            pTarget = pRoot->left;
        } else {
            pTarget = pRoot;
        }
        pAnswer = distanceK(pRoot, pTarget, testCase[i].k, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
