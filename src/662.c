#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define MAX_NODE_SIZE (3000)  // The number of nodes in the tree is in the range [1, 3000].
typedef struct {
    struct TreeNode* node;
    unsigned long long index;
} Pair;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int widthOfBinaryTree(struct TreeNode* root) {
    int retVal = 1;

    int levelSize = 0;
    Pair* pLevel = (Pair*)malloc(MAX_NODE_SIZE * sizeof(Pair));
    if (pLevel == NULL) {
        perror("malloc");
        return retVal;
    }
    pLevel[levelSize].node = root;
    pLevel[levelSize].index = 1LL;
    levelSize++;

    int tmpSize = 0;
    Pair* pTmp = (Pair*)malloc(MAX_NODE_SIZE * sizeof(Pair));
    if (pTmp == NULL) {
        perror("malloc");
        free(pLevel);
        pLevel = NULL;
        return retVal;
    }
    unsigned long long maxValue;
    int i;
    Pair* pSwap = NULL;
    while (levelSize > 0) {
        maxValue = retVal;
        retVal = fmax(maxValue, pLevel[levelSize - 1].index - pLevel[0].index + 1);

        tmpSize = 0;
        for (i = 0; i < levelSize; ++i) {
            if (pLevel[i].node->left) {
                pTmp[tmpSize].node = pLevel[i].node->left;
                pTmp[tmpSize].index = pLevel[i].index * 2;
                tmpSize++;
            }
            if (pLevel[i].node->right) {
                pTmp[tmpSize].node = pLevel[i].node->right;
                pTmp[tmpSize].index = pLevel[i].index * 2 + 1;
                tmpSize++;
            }
        }
        levelSize = tmpSize;
        pSwap = pLevel;
        pLevel = pTmp;
        pTmp = pSwap;
    }

    free(pLevel);
    pLevel = NULL;
    free(pTmp);
    pTmp = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3, 2, 5, 3, INT_MIN, 9}, 7},
                    {{1, 3, 2, 5, INT_MIN, INT_MIN, 9, 6, INT_MIN, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 7}, 14},
                    {{1, 3, 2, 5}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,3,2,5,3,null,9]
     *  Output: 4
     *
     *  Input: root = [1,3,2,5,null,null,9,6,null,7]
     *  Output: 7
     *
     *  Input: root = [1,3,2,5]
     *  Output: 2
     */

    struct TreeNode* pRoot = NULL;
    int answer;
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
        answer = widthOfBinaryTree(pRoot);
        printf("Output: %d\n", answer);

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
