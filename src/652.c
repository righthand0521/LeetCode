#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

typedef struct {
    char *key;
    struct TreeNode *val;
    UT_hash_handle hh;
} HashMapItem;
typedef struct {
    void *key;
    UT_hash_handle hh;
} HashSetItem;
char *inorder(struct TreeNode *node, HashMapItem **seen, HashSetItem **repeat) {
    char *pSerial = NULL;

    if (node == NULL) {
        return "";
    }

    char *pLeftStr = inorder(node->left, seen, repeat);
    char *pRightStr = inorder(node->right, seen, repeat);
    // -200 <= Node.val <= 200
    pSerial = (char *)calloc(8 + strlen(pLeftStr) + strlen(pRightStr), sizeof(char));
    if (pSerial == NULL) {
        perror("calloc");
        return "";
    }
    sprintf(pSerial, "(%s%d%s)", pLeftStr, node->val, pRightStr);

    HashMapItem *pHashMapEntry = NULL;
    HASH_FIND_STR(*seen, pSerial, pHashMapEntry);
    if (pHashMapEntry != NULL) {
        HashSetItem *pHashSetEntry = NULL;
        HASH_FIND_PTR(*repeat, &(pHashMapEntry->val), pHashSetEntry);
        if (pHashSetEntry == NULL) {
            pHashSetEntry = (HashSetItem *)malloc(sizeof(HashSetItem));
            if (pHashSetEntry == NULL) {
                perror("malloc");
                return "";
            }
            pHashSetEntry->key = (void *)pHashMapEntry->val;
            HASH_ADD_PTR(*repeat, key, pHashSetEntry);
        }
    } else {
        pHashMapEntry = (HashMapItem *)malloc(sizeof(HashMapItem));
        if (pHashMapEntry == NULL) {
            perror("malloc");
            return "";
        }
        pHashMapEntry->key = pSerial;
        pHashMapEntry->val = node;
        HASH_ADD_STR(*seen, key, pHashMapEntry);
    }

    return pSerial;
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
struct TreeNode **findDuplicateSubtrees(struct TreeNode *root, int *returnSize) {
    struct TreeNode **pRetVal = NULL;

    HashMapItem *seen = NULL;
    HashSetItem *repeat = NULL;
    inorder(root, &seen, &repeat);

    (*returnSize) = HASH_COUNT(repeat);
    pRetVal = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * (*returnSize));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int pos = 0;
    HashSetItem *pCurrent;
    HashSetItem *pTemp;
    HASH_ITER(hh, repeat, pCurrent, pTemp) {
        pRetVal[pos++] = (struct TreeNode *)pCurrent->key;
        HASH_DEL(repeat, pCurrent);
        free(pCurrent);
    }

    HashMapItem *pCurrentMap;
    HashMapItem *pTempMap;
    HASH_ITER(hh, seen, pCurrentMap, pTempMap) {
        HASH_DEL(seen, pCurrentMap);
        free(pCurrentMap->key);
        free(pCurrentMap);
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, 2, 3, 4, INT_MIN, 2, 4, INT_MIN, INT_MIN, 4}, 10, 0},
                    {{2, 1, 1}, 3, 0},
                    {{2, 2, 2, 3, INT_MIN, 3, INT_MIN}, 7, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,3,4,null,2,4,null,null,4]
     *  Output: [[2,4],[4]]
     *
     *  Input: root = [2,1,1]
     *  Output: [[1]]
     *
     *  Input: root = [2,2,2,3,null,3,null]
     *  Output: [[2,3],[3]]
     */

    struct TreeNode *pRoot = NULL;
    struct TreeNode **pAnswer = NULL;
    int height;
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
#if 0  // fix
        height = getTreeHeight(pRoot);
        showTreeOutput(pRoot, height);
        printf("\n");
#endif

        pAnswer = findDuplicateSubtrees(pRoot, &testCase[i].returnSize);
        printf("Output: [");
#if 1  // fix
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", j == 0 ? "" : ",");
            height = getTreeHeight(pAnswer[j]);
            showTreeOutput(pAnswer[j], height);
            printf("]");
        }
#endif
        printf("]\n");

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
