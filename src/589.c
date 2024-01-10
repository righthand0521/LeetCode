#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treeNary.h"

void preorderTraversal(struct Node* root, int* pTreeNodeCount, int* pTreeArray) {
    if (root == NULL) {
        return;
    }
    *(pTreeArray + (*pTreeNodeCount)) = root->val;
    (*pTreeNodeCount)++;
    int i;
    for (i = 0; i < root->numChildren; ++i) {
        preorderTraversal(root->children[i], pTreeNodeCount, pTreeArray);
    }
}
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorder(struct Node* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    if (root == NULL) {
        return pRetVal;
    }

    // The number of nodes in the tree is in the range [0, 10^4].
    pRetVal = (int*)malloc(10000 * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    preorderTraversal(root, returnSize, pRetVal);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,null,3,2,4,null,5,6]
     *  Output: [1,3,5,6,2,4]
     *
     *  Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
     *  Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]
     */

    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: root = [");
        printf("]\n");
    }

    return EXIT_SUCCESS;
}
