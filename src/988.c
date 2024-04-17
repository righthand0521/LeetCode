#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define MAX_RETURN_SIZE (8500 + 4)  // The number of nodes in the tree is in the range [1, 8500].
void dfs(struct TreeNode* root, char* currentStr, int currentStrIdx, char* answer, int* answerIdx) {
    if (root == NULL) {
        return;
    }

    currentStr[currentStrIdx] = root->val + 'a';
    if ((root->left == NULL) && (root->right == NULL)) {
        if (((*answerIdx) == 0) || (strcmp(&currentStr[currentStrIdx], &answer[(*answerIdx)]) < 0)) {
            (*answerIdx) = currentStrIdx;
            strcpy(&answer[(*answerIdx)], &currentStr[currentStrIdx]);
        }
        return;
    }

    if (root->left) {
        dfs(root->left, currentStr, currentStrIdx - 1, answer, answerIdx);
    }

    if (root->right) {
        dfs(root->right, currentStr, currentStrIdx - 1, answer, answerIdx);
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
char* smallestFromLeaf(struct TreeNode* root) {
    char* pRetVal = NULL;

    int pRetValIdx = 0;
    pRetVal = (char*)malloc(MAX_RETURN_SIZE * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (MAX_RETURN_SIZE * sizeof(char)));

    int pCurrentIdx = MAX_RETURN_SIZE - 2;
    char* pCurrent = (char*)malloc(MAX_RETURN_SIZE * sizeof(char));
    if (pCurrent == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pCurrent, 0, (MAX_RETURN_SIZE * sizeof(char)));

    dfs(root, pCurrent, pCurrentIdx, pRetVal, &pRetValIdx);
    if (pRetValIdx == 0) {
        memset(pRetVal, 0, (MAX_RETURN_SIZE * sizeof(char)));
    } else {
        memset(pCurrent, 0, (MAX_RETURN_SIZE * sizeof(char)));
        snprintf(pCurrent, MAX_RETURN_SIZE, "%s", pRetVal + pRetValIdx);
        memset(pRetVal, 0, (MAX_RETURN_SIZE * sizeof(char)));
        memcpy(pRetVal, pCurrent, (MAX_RETURN_SIZE * sizeof(char)));
    }

    free(pCurrent);
    pCurrent = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (8500)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{0, 1, 2, 3, 4, 3, 4}, 7},
                    {{25, 1, 3, 1, 3, 0, 2}, 7},
                    {{2, 2, 1, INT_MIN, 1, 0, INT_MIN, INT_MAX, INT_MAX, 0}, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [0,1,2,3,4,3,4]
     *  Output: "dba"
     *
     *  Input: root = [25,1,3,1,3,0,2]
     *  Output: "adz"
     *
     *  Input: root = [2,2,1,null,1,0,null,0]
     *  Output: "abc"
     */

    struct TreeNode* pRoot = NULL;
    char* answer;
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

        answer = smallestFromLeaf(pRoot);
        printf("Output: %s\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
        free(answer);
        answer = NULL;
    }

    return EXIT_SUCCESS;
}
