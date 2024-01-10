#include <math.h>
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
void inorderTraversal(struct TreeNode* root, int* previous, int* miniDiff) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left, previous, miniDiff);
    if ((*previous) != -1) {
        (*miniDiff) = fmin((*miniDiff), root->val - (*previous));
    }
    (*previous) = root->val;
    inorderTraversal(root->right, previous, miniDiff);
}
int getMinimumDifference(struct TreeNode* root) {
    int retVal = INT_MAX;

    // 0 <= Node.val <= 10^5
    int previous = -1;
    inorderTraversal(root, &previous, &retVal);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{4, 2, 6, 1, 3}, 5}, {{1, 0, 48, INT_MIN, INT_MIN, 12, 49}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [4,2,6,1,3]
     *  Output: 1
     *
     *  Input: root = [1,0,48,null,null,12,49]
     *  Output: 1
     */

    struct TreeNode* pRoot = NULL;
    int answer = 0;
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

        answer = getMinimumDifference(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
