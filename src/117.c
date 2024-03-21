#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treeNode.h"

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *left;
 *     struct Node *right;
 *     struct Node *next;
 * };
 */
struct Node* connect(struct Node* root) {
    struct Node* pRetVal = NULL;

    if (root == NULL) {
        return pRetVal;
    }

#define MAX_QUEUE_SIZE (12000)  // The number of nodes in the tree is in the range [0, 6000].
    struct Node* levelQueue[MAX_QUEUE_SIZE];
    int levelQueueHead = 0;
    int levelQueueTail = 0;
    levelQueue[levelQueueTail++] = root;

    int levelQueueSize;
    struct Node* pLast = NULL;
    struct Node* pNode = NULL;
    int i;
    while (levelQueueHead < levelQueueTail) {
        pLast = NULL;
        levelQueueSize = levelQueueTail - levelQueueHead;
        for (i = 1; i <= levelQueueSize; ++i) {
            pNode = levelQueue[levelQueueHead++];
            if (pNode->left) {
                levelQueue[levelQueueTail++] = pNode->left;
            }
            if (pNode->right) {
                levelQueue[levelQueueTail++] = pNode->right;
            }
            if (i != 1) {
                pLast->next = pNode;
            }
            pLast = pNode;
        }
    }
    pRetVal = root;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (6000)
    struct testCaseType {
        int root[MAX_SIZE];
        int rootSize;
    } testCase[] = {{{1, 2, 3, 4, 5, INT_MIN, 7}, 7}, {{}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,3,4,5,null,7]
     *  Output: [1,#,2,3,#,4,5,7,#]
     *
     *  Input: root = []
     *  Output: []
     */

    struct Node* pRoot = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: root = [");
        for (j = 0; j < testCase[i].rootSize; ++j) {
            if (testCase[i].root[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
                continue;
            }
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].root[j]);
        }
        printf("]\n");

        pRoot = buildNodeTree(testCase[i].root, testCase[i].rootSize, 0);
        pRoot = connect(pRoot);
        printf("Output: [");
        displayNodeTreeByNext(pRoot);
        printf("]\n");

        printf("\n");

        freeNodeTree(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
