#if (CPP)
#include <climits>
#include <limits>
#else
#include <limits.h>
#endif

#ifndef TREE_H
#define TREE_H

#if (CPP)
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
TreeNode* buildBinaryTree(vector<int>& nums, int index) {
    TreeNode* pRoot = nullptr;

    int len = nums.size();
    if (index >= len) {
        return pRoot;
    }

    if ((nums[index] == numeric_limits<int>::min()) || (nums[index] == numeric_limits<int>::max())) {
        return pRoot;
    }

    pRoot = new TreeNode(nums[index]);
    pRoot->left = buildBinaryTree(nums, 2 * index + 1);
    pRoot->right = buildBinaryTree(nums, 2 * index + 2);

    return pRoot;
}
#else
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
struct TreeNode* buildBinaryTree(int* nums, int numsSize, int index) {
    struct TreeNode* pRoot = NULL;

    if (index >= numsSize) {
        return pRoot;
    }

    if ((nums[index] == INT_MIN) || (nums[index] == INT_MAX)) {
        return pRoot;
    }

    pRoot = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (pRoot == NULL) {
        perror("malloc");
        return pRoot;
    }
    pRoot->val = nums[index];
    pRoot->left = buildBinaryTree(nums, numsSize, 2 * index + 1);
    pRoot->right = buildBinaryTree(nums, numsSize, 2 * index + 2);

    return pRoot;
}
#endif

void freeTreeNode(struct TreeNode* pRoot) {
#if (CPP)
    if (pRoot == nullptr) {
#else
    if (pRoot == NULL) {
#endif
        return;
    }

    freeTreeNode(pRoot->left);
    freeTreeNode(pRoot->right);

#if (CPP)
    delete pRoot;
#else
    free(pRoot);
#endif
}
int getTreeHeight(struct TreeNode* pRoot) {
#if (CPP)
    if (pRoot == nullptr) {
#else
    if (pRoot == NULL) {
#endif
        return 0;
    }

    int leftHeight = getTreeHeight(pRoot->left);
    int rightHeight = getTreeHeight(pRoot->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }

    return rightHeight + 1;
}
void printTreeLevel(struct TreeNode* pRoot, int level, int flag) {
#if (CPP)
    if (pRoot == nullptr) {
#else
    if (pRoot == NULL) {
#endif
        printf(",null");
        return;
    }

    if (level == 0) {
        printf("%s%d", (flag == 0) ? "" : ",", pRoot->val);
        return;
    }
    printTreeLevel(pRoot->left, level - 1, flag);
    printTreeLevel(pRoot->right, level - 1, flag);
}
void showTreeOutput(struct TreeNode* pRoot, int height) {
    int level;
    for (level = 0; level < height; ++level) {
        printTreeLevel(pRoot, level, level);
    }
}
#if (CPP)
TreeNode* findSubTree(struct TreeNode* pRoot, int value) {
    TreeNode* pRetVal = nullptr;

    if (pRoot == nullptr) {
        return pRetVal;
    }

    if (pRoot->val == value) {
        pRetVal = pRoot;
        return pRetVal;
    }

    pRetVal = findSubTree(pRoot->left, value);
    if (pRetVal != nullptr) {
        return pRetVal;
    }

    pRetVal = findSubTree(pRoot->right, value);
    if (pRetVal != nullptr) {
        return pRetVal;
    }

    return pRetVal;
}
#else
void findSubTree(struct TreeNode* pRoot, int value, struct TreeNode** pRetVal) {
    if (pRoot == NULL) {
        *pRetVal = pRoot;
        return;
    }

    if (pRoot->val == value) {
        *pRetVal = pRoot;
        return;
    }

    findSubTree(pRoot->left, value, pRetVal);
    if (*pRetVal != NULL) {
        return;
    }
    findSubTree(pRoot->right, value, pRetVal);
}
#endif

#endif  // TREE_H
