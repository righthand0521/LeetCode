#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treeNary.h"

int treeHeight(struct Node* pRoot) {
    int retVal = 0;

    if (pRoot == NULL) {
        return retVal;
    }

    int height = 0;
    int i;
    for (i = 0; i < pRoot->numChildren; ++i) {
        height = treeHeight(pRoot->children[i]);
        retVal = (retVal > height) ? retVal : height;
    }

    return retVal + 1;
}
void treeLevel(struct Node* pRoot, int level, int* pReturnArray, int* pReturnArrayIndex) {
    if (pRoot == NULL) {
        return;
    }

    if (level == 0) {
        if (pReturnArray != NULL) {
            pReturnArray[(*pReturnArrayIndex)] = pRoot->val;
        }
        (*pReturnArrayIndex)++;
        return;
    }

    int i;
    for (i = 0; i < pRoot->numChildren; ++i) {
        treeLevel(pRoot->children[i], level - 1, pReturnArray, pReturnArrayIndex);
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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct Node* root, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    //
    (*returnSize) = treeHeight(root);
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

    if (root == NULL) {
        (*returnSize) = 0;
        return pRetVal;
    }

    //
    int i;
    int index;
    int level;
    for (level = 0; level < (*returnSize); ++level) {
        pRetVal[level] = NULL;
        index = 0;
        treeLevel(root, level, pRetVal[level], &index);

        (*returnColumnSizes)[level] = index;
        pRetVal[level] = (int*)malloc(((*returnColumnSizes)[level]) * sizeof(int));
        if (pRetVal[level] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (i = 0; i < level - 1; ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            (*returnSize) = 0;
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[level], 0, ((*returnColumnSizes)[level]) * sizeof(int));

        index = 0;
        treeLevel(root, level, pRetVal[level], &index);
    }

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
     *  Output: [[1],[3,2,4],[5,6]]
     *
     *  Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
     *  Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]
     */

    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: root = [");
        printf("]\n");
    }

    return EXIT_SUCCESS;
}
