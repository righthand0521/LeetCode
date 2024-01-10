#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
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
void inorder(struct TreeNode* root, struct hashTable** pCounter) {
    if (root == NULL) {
        return;
    }

    inorder(root->left, pCounter);

    int key = root->val;
    struct hashTable* pTemp = NULL;
    HASH_FIND_INT(*pCounter, &key, pTemp);
    if (pTemp == NULL) {
        pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            return;
        }
        pTemp->key = key;
        pTemp->value = 1;
        HASH_ADD_INT(*pCounter, key, pTemp);
    } else {
        pTemp->value += 1;
    }

    inorder(root->right, pCounter);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMode(struct TreeNode* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    struct hashTable* pCounter = NULL;
    inorder(root, &pCounter);

    int maxValue = 0;
    struct hashTable* pTmp = NULL;
    for (pTmp = pCounter; pTmp != NULL; pTmp = pTmp->hh.next) {
        maxValue = fmax(maxValue, pTmp->value);
    }

#define MAX_TREE_NODE (int)(1e4)  // The number of nodes in the tree is in the range [1, 104].
    pRetVal = (int*)malloc(MAX_TREE_NODE * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (MAX_TREE_NODE * sizeof(int)));
    for (pTmp = pCounter; pTmp != NULL; pTmp = pTmp->hh.next) {
        if (pTmp->value == maxValue) {
            pRetVal[(*returnSize)++] = pTmp->key;
        }
    }

    freeAll(pCounter);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, INT_MIN, 2, INT_MAX, INT_MAX, 2}, 6, 0}, {{0}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,null,2,2]
     *  Output: [2]
     *
     *  Input: root = [0]
     *  Output: [0]
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

        pAnswer = findMode(pRoot, &testCase[i].returnSize);
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
