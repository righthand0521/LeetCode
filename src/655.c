#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define DFS (0)
#define BFS (1)
#define MAX_VAL_LEN (32)
#if (DFS)
int dfsDepth(struct TreeNode* root) {
    int retVal = 0;

    if (root->left) {
        retVal = fmax(retVal, dfsDepth(root->left) + 1);
    }
    if (root->right) {
        retVal = fmax(retVal, dfsDepth(root->right) + 1);
    }

    return retVal;
}
void dfs(char*** pRetVal, struct TreeNode* root, int row, int col, int height) {
    sprintf(pRetVal[row][col], "%d", root->val);
    if (root->left) {
        dfs(pRetVal, root->left, row + 1, col - (1 << (height - row - 1)), height);
    }
    if (root->right) {
        dfs(pRetVal, root->right, row + 1, col + (1 << (height - row - 1)), height);
    }
}
#elif (BFS)
#define MAX_NODE_SIZE (1024)

typedef struct {
    struct TreeNode* node;
    int row;
    int col;
} Tuple;

int bfsDepth(struct TreeNode* root) {
    int retVal = -1;

    struct TreeNode** bfsQueue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * MAX_NODE_SIZE);
    if (bfsQueue == NULL) {
        perror("malloc");
        return retVal;
    }
    int bfsHead = 0;
    int bfsTail = 0;
    bfsQueue[bfsTail++] = root;

    struct TreeNode* pTmp;
    int bfsQueueSize;
    while (bfsHead != bfsTail) {
        bfsQueueSize = bfsTail - bfsHead;
        retVal++;

        while (bfsQueueSize) {
            bfsQueueSize--;

            pTmp = bfsQueue[bfsHead++];
            if (pTmp->left) {
                bfsQueue[bfsTail++] = pTmp->left;
            }
            if (pTmp->right) {
                bfsQueue[bfsTail++] = pTmp->right;
            }
        }
    }
    free(bfsQueue);
    bfsQueue = NULL;

    return retVal;
}
Tuple* creatTuple(struct TreeNode* node, int row, int col) {
    Tuple* pObj = (Tuple*)malloc(sizeof(Tuple));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->node = node;
    pObj->row = row;
    pObj->col = col;

    return pObj;
}
void bfs(char*** pRetVal, struct TreeNode* root, int n, int height) {
    Tuple** bfsQueue = (Tuple**)malloc(sizeof(Tuple*) * n);
    if (bfsQueue == NULL) {
        perror("malloc");
        return;
    }
    int bfsHead = 0;
    int bfsTail = 0;
    bfsQueue[bfsTail++] = creatTuple(root, 0, (n - 1) / 2);

    int row, col;
    Tuple* pTmp;
    while (bfsHead != bfsTail) {
        pTmp = bfsQueue[bfsHead++];

        row = pTmp->row;
        col = pTmp->col;
        sprintf(pRetVal[row][col], "%d", pTmp->node->val);
        if (pTmp->node->left) {
            bfsQueue[bfsTail++] = creatTuple(pTmp->node->left, row + 1, col - (1 << (height - row - 1)));
        }
        if (pTmp->node->right) {
            bfsQueue[bfsTail++] = creatTuple(pTmp->node->right, row + 1, col + (1 << (height - row - 1)));
        }
    }

    int i;
    for (i = 0; i < bfsTail; i++) {
        free(bfsQueue[i]);
        bfsQueue[i] = NULL;
    }
    free(bfsQueue);
    bfsQueue = NULL;
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
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** printTree(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    char*** pRetVal = NULL;

#if (DFS)
    int height = dfsDepth(root);
    int m = height + 1;
    int n = (1 << (height + 1)) - 1;
#elif (BFS)
    int height = bfsDepth(root);
    int m = height + 1;
    int n = (1 << (height + 1)) - 1;
#endif

    (*returnSize) = 0;
    pRetVal = (char***)malloc(sizeof(char**) * m);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    int i, j;
    for (i = 0; i < m; i++) {
        pRetVal[i] = (char**)malloc(sizeof(char*) * n);
        if (pRetVal[i] == NULL) {
            perror("malloc");
            return pRetVal;
        }
        for (j = 0; j < n; j++) {
            pRetVal[i][j] = (char*)malloc(sizeof(char) * MAX_VAL_LEN);
            if (pRetVal[i][j] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pRetVal[i][j][0] = '\0';
        }
    }
    (*returnColumnSizes) = (int*)malloc(sizeof(int) * m);
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < m; i++) {
        (*returnColumnSizes)[i] = n;
    }
    (*returnSize) = m;

#if (DFS)
    printf("Depth-First Search\n\n");
    dfs(pRetVal, root, 0, (n - 1) / 2, height);
#elif (BFS)
    printf("Breadth-First Search\n\n");
    bfs(pRetVal, root, n, height);
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1024)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{1, 2}, 2, 0, NULL}, {{1, 2, 3, INT_MIN, 4}, 5, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2]
     *  Output:
     *  [["","1",""],
     *   ["2","",""]]
     *
     *  Input: root = [1,2,3,null,4]
     *  Output:
     *  [["","","","1","","",""],
     *   ["","2","","","","3",""],
     *   ["","","4","","","",""]]
     */

    struct TreeNode* pRoot = NULL;
    char*** pAnswer = NULL;
    int i, j, k;
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

        pAnswer = printTree(pRoot, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                free(pAnswer[j][k]);
                pAnswer[j][k] = NULL;
            }
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
    }

    return EXIT_SUCCESS;
}
