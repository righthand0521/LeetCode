#include <limits.h>

#ifndef TREE_NODE_H
#define TREE_NODE_H

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
    struct Node* next;
};
void createNodeTree(struct Node** pRoot, int* nums, int index, int numsSize) {
    if (index < numsSize) {
        if (nums[index] == INT_MIN) {
            return;
        }
        if (nums[index] == INT_MAX) {
            return;
        }

        *pRoot = malloc(sizeof(**pRoot));
        if (pRoot == NULL) {
            perror("malloc");
            return;
        }
        (*pRoot)->val = nums[index];
        (*pRoot)->left = NULL;
        (*pRoot)->right = NULL;
        (*pRoot)->next = NULL;

        createNodeTree(&(*pRoot)->left, nums, 2 * index + 1, numsSize);
        createNodeTree(&(*pRoot)->right, nums, 2 * index + 2, numsSize);
    }
}
void displayNodeTree(struct Node* pRoot, int level) {
    if (pRoot) {
        displayNodeTree(pRoot->right, level + 1);
        printf("%*s->%d\n", 4 * level, "", pRoot->val);
        displayNodeTree(pRoot->left, level + 1);
    }
}
void displayNodeTreeByNext(struct Node* pRoot) {
    if (pRoot) {
        struct Node* p = pRoot;
        while (p != NULL) {
            printf("%d,", p->val);
            p = p->next;
        }
        printf("#,");
        displayNodeTreeByNext(pRoot->left);
    }
}
void freeNodeTree(struct Node* pRoot) {
    if (pRoot != NULL) {
        freeNodeTree(pRoot->left);
        freeNodeTree(pRoot->right);
        free(pRoot);
    }
}

#endif  // TREE_NODE_H
