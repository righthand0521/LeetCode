#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root) {
    char* pRetVal = NULL;

    return pRetVal;
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) {
    struct TreeNode* pRetVal = NULL;

    return pRetVal;
}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int n;
    } testCase[] = {};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [2,1,3]
     *  Output: [2,1,3]
     *
     *  Input: root = []
     *  Output: []
     */

    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("\n");
    }

    return EXIT_SUCCESS;
}
