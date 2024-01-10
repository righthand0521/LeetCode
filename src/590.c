#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treeNary.h"

void postorderTraversal(struct Node* root, int* pTreeNodeCount, int* pTreeArray) {
    if (root == NULL) {
        return;
    }
    int i;
    for (i = 0; i < root->numChildren; ++i) {
        postorderTraversal(root->children[i], pTreeNodeCount, pTreeArray);
    }
    *(pTreeArray + (*pTreeNodeCount)) = root->val;
    (*pTreeNodeCount) = (*pTreeNodeCount) + 1;
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
int* postorder(struct Node* root, int* returnSize) {
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
    postorderTraversal(root, returnSize, pRetVal);

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
     *  Output: [5,6,3,2,4,1]
     *
     *  Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
     *  Output: [2,6,14,11,7,3,12,8,4,13,9,10,5,1]
     */

    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: root = [");
        printf("]\n");
    }

    return EXIT_SUCCESS;
}
