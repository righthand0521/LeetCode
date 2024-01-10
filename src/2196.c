#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

typedef struct {
    int key;
    struct TreeNode* value;
    UT_hash_handle hh;
} HashMapTree;
typedef struct {
    int key;
    int value;
    UT_hash_handle hh;
} HashMapChild;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* createBinaryTree(int** descriptions, int descriptionsSize, int* descriptionsColSize) {
    struct TreeNode* pRetVal = NULL;

    HashMapTree* pTreeHashTable = NULL;
    HashMapTree *pParent, *pChild;
    HashMapChild* pChildHashTable = NULL;
    HashMapChild* pChildDegree;
    int parent, child, isLeft;
    int i;
    for (i = 0; i < descriptionsSize; ++i) {
        parent = descriptions[i][0];
        child = descriptions[i][1];
        isLeft = descriptions[i][2];

        // parent node
        pParent = NULL;
        HASH_FIND_INT(pTreeHashTable, &parent, pParent);
        if (pParent == NULL) {
            pParent = (HashMapTree*)malloc(sizeof(HashMapTree));
            if (pParent == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pParent->key = parent;
            pParent->value = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            if (pParent->value == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pParent->value->val = parent;
            pParent->value->left = NULL;
            pParent->value->right = NULL;
            HASH_ADD_INT(pTreeHashTable, key, pParent);
        }
        // parent degree
        pChildDegree = NULL;
        HASH_FIND_INT(pChildHashTable, &parent, pChildDegree);
        if (pChildDegree == NULL) {
            pChildDegree = (HashMapChild*)malloc(sizeof(HashMapChild));
            if (pChildDegree == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pChildDegree->key = parent;
            pChildDegree->value = 0;
            HASH_ADD_INT(pChildHashTable, key, pChildDegree);
        }

        // child node
        pChild = NULL;
        HASH_FIND_INT(pTreeHashTable, &child, pChild);
        if (pChild == NULL) {
            pChild = (HashMapTree*)malloc(sizeof(HashMapTree));
            if (pChild == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pChild->key = child;
            pChild->value = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            if (pChild->value == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pChild->value->val = child;
            pChild->value->left = NULL;
            pChild->value->right = NULL;
            HASH_ADD_INT(pTreeHashTable, key, pChild);
        }
        // child degree
        pChildDegree = NULL;
        HASH_FIND_INT(pChildHashTable, &child, pChildDegree);
        if (pChildDegree == NULL) {
            pChildDegree = (HashMapChild*)malloc(sizeof(HashMapChild));
            if (pChildDegree == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pChildDegree->key = child;
            pChildDegree->value = 1;
            HASH_ADD_INT(pChildHashTable, key, pChildDegree);
        } else {
            pChildDegree->value += 1;
        }

        // isLeft
        if (isLeft == 1) {
            pParent->value->left = pChild->value;
        } else {
            pParent->value->right = pChild->value;
        }
    }

    // get root by degree
    parent = 0;
    HashMapChild* pCurrentChild;
    HashMapChild* pTempChild;
    HASH_ITER(hh, pChildHashTable, pCurrentChild, pTempChild) {
        if (pCurrentChild->value == 0) {
            parent = pCurrentChild->key;
        }
        HASH_DEL(pChildHashTable, pCurrentChild);
        free(pCurrentChild);
    }
    // get root node to return value
    HashMapTree* pCurrentParent;
    HashMapTree* pTempParent;
    HASH_ITER(hh, pTreeHashTable, pCurrentParent, pTempParent) {
        if (pCurrentParent->value->val == parent) {
            pRetVal = pCurrentParent->value;
        }
        HASH_DEL(pTreeHashTable, pCurrentParent);
        free(pCurrentParent);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_DESCRIPTIONS_ROW (int)(1e4)
#define MAX_DESCRIPTIONS_COL (3)
    struct testCaseType {
        int descriptions[MAX_DESCRIPTIONS_ROW][MAX_DESCRIPTIONS_COL];
        int descriptionsSize;
        int descriptionsColSize[MAX_DESCRIPTIONS_ROW];
    } testCase[] = {{{{20, 15, 1}, {20, 17, 0}, {50, 20, 1}, {50, 80, 0}, {80, 19, 1}}, 5, {3, 3, 3, 3, 3}},
                    {{{1, 2, 1}, {2, 3, 0}, {3, 4, 1}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
     *  Output: [50,20,80,15,17,19]
     *
     *  Input: descriptions = [[1,2,1],[2,3,0],[3,4,1]]
     *  Output: [1,2,null,null,3,4]
     */

    int** pDescriptions = NULL;
    struct TreeNode* pAnswer = NULL;
    int height;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: descriptions = [");
        for (j = 0; j < testCase[i].descriptionsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].descriptionsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].descriptions[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pDescriptions = (int**)malloc(testCase[i].descriptionsSize * sizeof(int*));
        if (pDescriptions == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].descriptionsSize; ++j) {
            pDescriptions[j] = (int*)malloc(testCase[i].descriptionsColSize[j] * sizeof(int));
            if (pDescriptions[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pDescriptions[k]);
                }
                free(pDescriptions);
                return EXIT_FAILURE;
            }
            memset(pDescriptions[j], 0, (testCase[i].descriptionsColSize[j] * sizeof(int)));
            memcpy(pDescriptions[j], testCase[i].descriptions[j], (testCase[i].descriptionsColSize[j] * sizeof(int)));
        }

        pAnswer = createBinaryTree(pDescriptions, testCase[i].descriptionsSize, testCase[i].descriptionsColSize);
        height = getTreeHeight(pAnswer);
        printf("Output: [");
        showTreeOutput(pAnswer, height);
        printf("]\n");

        printf("\n");

        freeTreeNode(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].descriptionsSize; ++j) {
            free(pDescriptions[j]);
        }
        free(pDescriptions);
        pDescriptions = NULL;
    }

    return EXIT_SUCCESS;
}
