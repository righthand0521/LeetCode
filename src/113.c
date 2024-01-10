#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define DFS (1)
#define BFS (1)
#define MAX_RETURN_SIZE (5000)  // The number of nodes in the tree is in the range [0, 5000].
#if (DFS)
void dfs(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes, int** retVal, int* path,
         int* pathSize) {
    if (root == NULL) {
        return;
    }

    path[(*pathSize)] = root->val;
    (*pathSize) += 1;

    targetSum -= root->val;

    int i;
    if ((root->left == NULL) && (root->right == NULL) && (targetSum == 0)) {
        retVal[(*returnSize)] = (int*)malloc((*pathSize) * sizeof(int));
        if (retVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*returnSize); ++i) {
                free(retVal[i]);
                retVal[i] = NULL;
            }
            return;
        }
        memset(retVal[(*returnSize)], 0, ((*pathSize) * sizeof(int)));
        memcpy(retVal[(*returnSize)], path, ((*pathSize) * sizeof(int)));
        (*returnColumnSizes)[(*returnSize)] = (*pathSize);
        (*returnSize) += 1;
    }
    dfs(root->left, targetSum, returnSize, returnColumnSizes, retVal, path, pathSize);
    dfs(root->right, targetSum, returnSize, returnColumnSizes, retVal, path, pathSize);

    (*pathSize) -= 1;
}
#elif (BFS)
struct hashTable {
    struct TreeNode* key;
    struct TreeNode* value;
    UT_hash_handle hh;
};
struct hashTable* parent = NULL;
void insertHashTable(struct TreeNode* x, struct TreeNode* y) {
    struct hashTable* pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (pTmp == NULL) {
        perror("mallpc");
        return;
    }
    pTmp->key = x;
    pTmp->value = y;

    HASH_ADD_PTR(parent, key, pTmp);
}
struct TreeNode* queryHashTable(struct TreeNode* x) {
    struct hashTable* pTmp;
    HASH_FIND_PTR(parent, &x, pTmp);

    return pTmp->value;
}
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
void bfs(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes, int** retVal) {
    if (root == NULL) {
        return;
    }

    insertHashTable(root, NULL);

    struct TreeNode* bfsQueue[MAX_RETURN_SIZE];
    int targetSumQueue[MAX_RETURN_SIZE];
    int bfsHead = 0;
    int bfsTail = 0;
    bfsQueue[bfsTail] = root;
    targetSumQueue[bfsTail] = 0;
    bfsTail++;

    int i, colSize, tmp;
    struct TreeNode* node = NULL;
    int sum;
    while (bfsHead < bfsTail) {
        node = bfsQueue[bfsHead];
        sum = targetSumQueue[bfsHead] + node->val;
        bfsHead++;

        if ((node->left == NULL) && (node->right == NULL)) {
            if (sum == targetSum) {
                retVal[(*returnSize)] = (int*)malloc(MAX_RETURN_SIZE * sizeof(int));
                if (retVal[(*returnSize)] == NULL) {
                    perror("malloc");
                    for (i = 0; i < (*returnSize); ++i) {
                        free(retVal[i]);
                        retVal[i] = NULL;
                    }
                    freeAll(parent);
                    parent = NULL;
                    return;
                }

                colSize = 0;
                while (node != NULL) {
                    retVal[(*returnSize)][colSize++] = node->val;
                    node = queryHashTable(node);
                }

                for (i = 0; i < colSize / 2; i++) {
                    tmp = retVal[(*returnSize)][i];
                    retVal[(*returnSize)][i] = retVal[(*returnSize)][colSize - 1 - i];
                    retVal[(*returnSize)][colSize - 1 - i] = tmp;
                }
                (*returnColumnSizes)[(*returnSize)] = colSize;
                (*returnSize) += 1;
            }
        } else {
            if (node->left != NULL) {
                insertHashTable(node->left, node);
                bfsQueue[bfsTail] = node->left;
                targetSumQueue[bfsTail] = sum;
                bfsTail++;
            }
            if (node->right != NULL) {
                insertHashTable(node->right, node);
                bfsQueue[bfsTail] = node->right;
                targetSumQueue[bfsTail] = sum;
                bfsTail++;
            }
        }
    }

    freeAll(parent);
    parent = NULL;
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
int** pathSum(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    pRetVal = (int**)malloc(MAX_RETURN_SIZE * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    (*returnColumnSizes) = (int*)malloc(MAX_RETURN_SIZE * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (MAX_RETURN_SIZE * sizeof(int)));

#if (DFS)
    printf("Depth-First Search\n\n");

    int* path = NULL;
    path = (int*)malloc(MAX_RETURN_SIZE * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(path, 0, (MAX_RETURN_SIZE * sizeof(int)));
    int pathSize = 0;

    dfs(root, targetSum, returnSize, returnColumnSizes, pRetVal, path, &pathSize);
    free(path);
    path = NULL;
#elif (BFS)
    printf("Breadth-First Search\n\n");

    bfs(root, targetSum, returnSize, returnColumnSizes, pRetVal);
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int targetSum;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{5, 4, 8, 11, INT_MIN, 13, 4, 7, 2, INT_MAX, INT_MAX, INT_MIN, INT_MIN, 5, 1}, 15, 22, 0, NULL},
                    {{1, 2, 3}, 3, 5, 0, NULL},
                    {{1, 2}, 2, 0, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
     *  Output: [[5,4,11,2],[5,8,4,5]]
     *
     *  Input: root = [1,2,3], targetSum = 5
     *  Output: []
     *
     *  Input: root = [1,2], targetSum = 0
     *  Output: []
     */

    struct TreeNode* pRoot = NULL;
    int** pAnswer = NULL;
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
        printf("], targetSum = %d\n", testCase[i].targetSum);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        pAnswer = pathSum(pRoot, testCase[i].targetSum, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
