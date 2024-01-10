#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define ITERATIVELY (0)
#define RECURSIVELY (1)
#if (ITERATIVELY)
typedef struct Node {
    struct TreeNode* tree;
    struct Node* next;
} Node;

void stack_push(struct Node** pTop, struct TreeNode* pRoot) {
    Node* pNew = (Node*)malloc(sizeof(struct Node));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->tree = pRoot;
    pNew->next = (*pTop);
    *(pTop) = pNew;
}
struct TreeNode* stack_pop(struct Node** pTop) {
    struct TreeNode* pRetVal = NULL;

    Node* pHead = (*pTop);
    if (pHead == NULL) {
        printf("Stack is Empty");
        return pRetVal;
    }
    pRetVal = pHead->tree;
    (*pTop) = pHead->next;
    free(pHead);

    return pRetVal;
}
bool stack_empty(struct Node* pTop) {
    bool retVal = false;

    Node* pHead = pTop;
    if (pHead == NULL) {
        retVal = true;
    }

    return retVal;
}
void stack_free(struct Node** pTop) {
    Node* pFree = (*pTop);
    while ((*pTop) != NULL) {
        (*pTop) = (*pTop)->next;
        free(pFree);
        pFree = (*pTop);
    }
}
#elif (RECURSIVELY)
#endif
bool isMirror(struct TreeNode* left, struct TreeNode* right) {
    bool retVal = true;

    if ((left == NULL) && (right == NULL)) {
        return retVal;
    }

    if ((left == NULL) || (right == NULL)) {
        retVal = false;
        return retVal;
    }

    /* For two trees to be mirror images, the following three conditions must be true
     *  1. Their root node's key must be same
     *  2. left subtree of left tree and right subtree of right tree have to be mirror images
     *  3. right subtree of left tree and left subtree of right tree have to be mirror images
     */
#if (ITERATIVELY)
    Node* pTop = NULL;
    struct TreeNode* popLeft;
    struct TreeNode* popRight;

    stack_push(&pTop, left);
    stack_push(&pTop, right);
    while (stack_empty(pTop) == false) {
        popRight = stack_pop(&pTop);
        popLeft = stack_pop(&pTop);

        if (popLeft->val != popRight->val) {
            retVal = false;
            break;
        }

        if ((popLeft->left != NULL) && (popRight->right != NULL)) {
            stack_push(&pTop, popLeft->left);
            stack_push(&pTop, popRight->right);
        } else if ((popLeft->left == NULL) && (popRight->right != NULL)) {
            retVal = false;
            break;
        } else if ((popLeft->left != NULL) && (popRight->right == NULL)) {
            retVal = false;
            break;
        }

        if ((popLeft->right != NULL) && (popRight->left != NULL)) {
            stack_push(&pTop, popLeft->right);
            stack_push(&pTop, popRight->left);
        } else if ((popLeft->right == NULL) && (popRight->left != NULL)) {
            retVal = false;
            break;
        } else if ((popLeft->right != NULL) && (popRight->left == NULL)) {
            retVal = false;
            break;
        }
    }
    stack_free(&pTop);
    pTop = NULL;
#elif (RECURSIVELY)
    if (left->val != right->val) {
        retVal = false;
        return retVal;
    }

    retVal = (isMirror(left->left, right->right)) && (isMirror(left->right, right->left));
#endif

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
bool isSymmetric(struct TreeNode* root) {
    bool retVal = true;

    if (root == NULL) {
        return retVal;
    }
    retVal = isMirror(root->left, root->right);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 2, 3, 4, 4, 3}, 7}, {{1, 2, 2, INT_MIN, 3, INT_MIN, 3}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: root = [1,2,2,3,4,4,3]
     *  Output: true
     *
     *  Input: root = [1,2,2,null,3,null,3]
     *  Output: false
     */

    struct TreeNode* pRoot = NULL;
    bool answer = true;
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

        answer = isSymmetric(pRoot);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        freeTreeNode(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
