#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

bool findPath(struct TreeNode* node, int target, char* path, int* pathSize) {
    bool retVal = false;

    if (node == NULL) {
        return retVal;
    }

    if (node->val == target) {
        retVal = true;
        return retVal;
    }

    // Try left subtree
    path[(*pathSize)] = 'L';
    (*pathSize) += 1;
    if (findPath(node->left, target, path, pathSize)) {
        retVal = true;
        return retVal;
    }

    // Remove last character
    path[(*pathSize)] = '\0';
    (*pathSize) -= 1;

    // Try right subtree
    path[(*pathSize)] = 'R';
    (*pathSize) += 1;
    if (findPath(node->right, target, path, pathSize)) {
        return true;
    }

    // Remove last character
    path[(*pathSize)] = '\0';
    (*pathSize) -= 1;

    return retVal;
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
char* getDirections(struct TreeNode* root, int startValue, int destValue) {
    char* pRetVal = NULL;

    // Find paths from root to start and destination nodes
    int maxSize = (1e5);  // The number of nodes in the tree is n. 2 <= n <= 10 ^ 5
    char* pPath = (char*)malloc(maxSize * sizeof(char));
    if (pPath == NULL) {
        perror("malloc");
        return pRetVal;
    }
    //
    int startPathSize = 0;
    memset(pPath, 0, (maxSize * sizeof(char)));
    findPath(root, startValue, pPath, &startPathSize);
    char startPath[startPathSize + 1];
    memset(startPath, 0, sizeof(startPath));
    snprintf(startPath, sizeof(startPath), "%s", pPath);
    //
    int destPathSize = 0;
    memset(pPath, 0, (maxSize * sizeof(char)));
    findPath(root, destValue, pPath, &destPathSize);
    char destPath[destPathSize + 1];
    memset(destPath, 0, sizeof(destPath));
    snprintf(destPath, sizeof(destPath), "%s", pPath);
    //
    free(pPath);
    pPath = NULL;

    //
    int returnSize = startPathSize + destPathSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    // Find the length of the common path
    int commonPathLength = 0;
    while ((commonPathLength < startPathSize) && (commonPathLength < destPathSize) &&
           (startPath[commonPathLength] == destPath[commonPathLength])) {
        commonPathLength++;
    }

    // Add "U" for each step to go up from start to common ancestor
    returnSize = 0;
    int i;
    for (i = 0; i < startPathSize - commonPathLength; i++) {
        pRetVal[returnSize++] = 'U';
    }
    // Add directions from common ancestor to destination
    for (i = commonPathLength; i < destPathSize; i++) {
        pRetVal[returnSize++] = destPath[i];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int startValue;
        int destValue;
    } testCase[] = {{{5, 1, 2, 3, INT_MIN, 6, 4}, 7, 3, 6}, {{2, 1}, 2, 2, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
     *  Output: "UURL"
     *
     *  Input: root = [2,1], startValue = 2, destValue = 1
     *  Output: "L"
     */

    struct TreeNode* pRoot = NULL;
    char* pAnswer = NULL;
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
        printf("], startValue = %d, destValue = %d\n", testCase[i].startValue, testCase[i].destValue);
        pRoot = buildBinaryTree(testCase[i].nums, testCase[i].numsSize, 0);

        pAnswer = getDirections(pRoot, testCase[i].startValue, testCase[i].destValue);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
