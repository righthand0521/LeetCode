#include <ctype.h>
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
struct TreeNode* recoverFromPreorder(char* traversal) {
    struct TreeNode* pRetVal = NULL;

    int traversalSize = strlen(traversal);

    struct TreeNode* stack[traversalSize + 1];
    int stackTop = -1;

    struct TreeNode* node;
    int depth, value;
    int index = 0;
    while (index < traversalSize) {
        // Count the number of dashes
        depth = 0;
        while ((index < traversalSize) && (traversal[index] == '-')) {
            depth++;
            index++;
        }

        // Extract the node value
        value = 0;
        while ((index < traversalSize) && (isdigit(traversal[index]))) {
            value = value * 10 + (traversal[index] - '0');
            index++;
        }

        // Create the current node
        node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        if (node == NULL) {
            perror("malloc");
            return pRetVal;
        }
        node->val = value;
        node->left = NULL;
        node->right = NULL;

        // Adjust the stack to the correct depth
        while ((stackTop + 1) > depth) {
            stack[stackTop--] = NULL;
        }

        // Attach the node to the parent
        if (stackTop > -1) {
            if (stack[stackTop]->left == NULL) {
                stack[stackTop]->left = node;
            } else {
                stack[stackTop]->right = node;
            }
        }

        // Push the current node onto the stack
        stack[++stackTop] = node;
    }

    // The root is the first node in the stack
    pRetVal = stack[0];

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char traversal[MAX_SIZE];
    } testCase[] = {{"1-2--3--4-5--6--7"}, {"1-2--3---4-5--6---7"}, {"1-401--349---90--88"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: traversal = "1-2--3--4-5--6--7"
     *  Output: [1,2,5,3,4,6,7]
     *
     *  Input: traversal = "1-2--3---4-5--6---7"
     *  Output: [1,2,5,3,null,6,null,4,null,7]
     *
     *  Input: traversal = "1-401--349---90--88"
     *  Output: [1,401,null,349,88,90]
     */

    struct TreeNode* pAnswer = NULL;
    int height;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: traversal = \"%s\"\n", testCase[i].traversal);

        pAnswer = recoverFromPreorder(testCase[i].traversal);
        height = getTreeHeight(pAnswer);
        printf("Output: [");
        showTreeOutput(pAnswer, height);
        printf("]\n");

        printf("\n");

        freeTreeNode(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
