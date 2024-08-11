#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

int getTreeSize(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }
    retVal = 1 + getTreeSize(root->left) + getTreeSize(root->right);

    return retVal;
}
void inorder(struct TreeNode* root, int* pRetVal, int* returnSize) {
    if (root == NULL) {
        return;
    }
    inorder(root->left, pRetVal, returnSize);
    pRetVal[(*returnSize)++] = root->val;
    inorder(root->right, pRetVal, returnSize);
}
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(getTreeSize(root) * sizeof(int));
    inorder(root, pRetVal, returnSize);

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
typedef struct {
    int* returnValue;
    int returnSize;
    int index;
} BSTIterator;
BSTIterator* bSTIteratorCreate(struct TreeNode* root) {
    BSTIterator* pRetVal = NULL;

    pRetVal = (BSTIterator*)malloc(sizeof(BSTIterator));
    pRetVal->returnValue = inorderTraversal(root, &(pRetVal->returnSize));
    pRetVal->index = 0;

    return pRetVal;
}
int bSTIteratorNext(BSTIterator* obj) {
    int retVal = obj->returnValue[obj->index];
    obj->index += 1;

    return retVal;
}
bool bSTIteratorHasNext(BSTIterator* obj) {
    bool retVal = false;

    if (obj->index < obj->returnSize) {
        retVal = true;
    }

    return retVal;
}
void bSTIteratorFree(BSTIterator* obj) {
    free(obj->returnValue);
    obj->returnValue = NULL;
    free(obj);
    obj = NULL;
}
/**
 * Your BSTIterator struct will be instantiated and called as such:
 * BSTIterator* obj = bSTIteratorCreate(root);
 * int param_1 = bSTIteratorNext(obj);
 * bool param_2 = bSTIteratorHasNext(obj);
 * bSTIteratorFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e3)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][MAX_SIZE];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {
        {{"BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"},
         {{7, 3, 15, INT_MIN, INT_MIN, 9, 20}, {}, {}, {}, {}, {}, {}, {}, {}, {}},
         {7, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
     *  [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
     *  Output
     *  [null, 3, 7, true, 9, true, 15, true, 20, false]
     */

    BSTIterator* pBSTIterator = NULL;
    struct TreeNode* pRoot = NULL;
    int retIntValue;
    bool retBoolValue;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("\"%s\"%s", testCase[i].methods[j], (j == (testCase[i].calls - 1) ? "" : ","));
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            if (strcmp(testCase[i].methods[j], "BSTIterator") == 0) {
                printf("[");
                for (k = 0; k < testCase[i].valSize[j]; ++k) {
                    if (testCase[i].val[j][k] == INT_MIN) {
                        printf("%snull", (k == 0 ? "" : ","));
                    } else if (testCase[i].val[j][k] == INT_MAX) {
                        continue;
                    } else {
                        printf("%s%d", (k == 0 ? "" : ","), testCase[i].val[j][k]);
                    }
                }
                printf("]");
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "BSTIterator") == 0) {
                pRoot = buildBinaryTree(testCase[i].val[j], testCase[i].valSize[j], 0);
                pBSTIterator = bSTIteratorCreate(pRoot);
                printf("%s%s", "null", (j == (testCase[i].calls - 1) ? "" : ","));
            } else if (strcmp(testCase[i].methods[j], "next") == 0) {
                retIntValue = bSTIteratorNext(pBSTIterator);
                printf("%d%s", retIntValue, (j == (testCase[i].calls - 1) ? "" : ","));
            } else if (strcmp(testCase[i].methods[j], "hasNext") == 0) {
                retBoolValue = bSTIteratorHasNext(pBSTIterator);
                printf("%s%s", (retBoolValue == true ? "true" : "false"), (j == (testCase[i].calls - 1) ? "" : ","));
            }
        }
        printf("]\n");
        bSTIteratorFree(pBSTIterator);
        pBSTIterator = NULL;
        freeTreeNode(pRoot);
        pRoot = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
