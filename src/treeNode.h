#if (CPP)
#include <climits>
#include <limits>
#else
#include <limits.h>
#endif

#ifndef TREE_NODE_H
#define TREE_NODE_H

#if (CPP)
struct Node {
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(nullptr), right(nullptr) {}
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
    Node(int x, Node* left, Node* right) : val(x), left(left), right(right) {}
};
Node* buildNodeTree(vector<int>& nums, int index) {
    Node* pRoot = nullptr;

    int len = nums.size();
    if (index >= len) {
        return pRoot;
    }

    if ((nums[index] == numeric_limits<int>::min()) || (nums[index] == numeric_limits<int>::max())) {
        return pRoot;
    }

    pRoot = new Node(nums[index]);
    pRoot->left = buildNodeTree(nums, 2 * index + 1);
    pRoot->right = buildNodeTree(nums, 2 * index + 2);
    pRoot->next = nullptr;

    return pRoot;
}
#else
struct Node {
    int val;
    struct Node* left;
    struct Node* right;
    struct Node* next;
};
struct Node* buildNodeTree(int* nums, int numsSize, int index) {
    struct Node* pRoot = NULL;

    if (index >= numsSize) {
        return pRoot;
    }

    if ((nums[index] == INT_MIN) || (nums[index] == INT_MAX)) {
        return pRoot;
    }

    pRoot = (struct Node*)malloc(sizeof(struct Node));
    if (pRoot == NULL) {
        perror("malloc");
        return pRoot;
    }
    pRoot->val = nums[index];
    pRoot->left = buildNodeTree(nums, numsSize, 2 * index + 1);
    pRoot->right = buildNodeTree(nums, numsSize, 2 * index + 2);
    pRoot->next = NULL;

    return pRoot;
}
#endif

void freeNodeTree(struct Node* pRoot) {
#if (CPP)
    if (pRoot == nullptr) {
#else
    if (pRoot == NULL) {
#endif
        return;
    }

    freeNodeTree(pRoot->left);
    freeNodeTree(pRoot->right);

#if (CPP)
    delete pRoot;
#else
    free(pRoot);
#endif
}
void displayNodeTreeByNext(struct Node* pRoot) {
#if (CPP)
    if (pRoot == nullptr) {
#else
    if (pRoot == NULL) {
#endif
        return;
    }

    struct Node* p = pRoot;
    while (p != NULL) {
#if (CPP)
        cout << p->val << ",";
#else
        printf("%d,", p->val);
#endif
        p = p->next;
    }
#if (CPP)
    cout << "#,";
#else
    printf("#,");
#endif
    displayNodeTreeByNext(pRoot->left);
}

#endif  // TREE_NODE_H
