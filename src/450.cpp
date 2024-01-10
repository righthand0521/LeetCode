#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#include "tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        TreeNode* pRetVal = root;

        TreeNode* current = root;
        TreeNode* currentParent = nullptr;
        while ((current != nullptr) && (current->val != key)) {
            currentParent = current;
            if (current->val > key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (current == nullptr) {
            return pRetVal;
        }

        if ((current->left == nullptr) && (current->right == nullptr)) {
            current = nullptr;
        } else if (current->right == nullptr) {
            current = current->left;
        } else if (current->left == nullptr) {
            current = current->right;
        } else {
            TreeNode* successor = current->right;
            TreeNode* successorParent = current;
            while (successor->left) {
                successorParent = successor;
                successor = successor->left;
            }

            if (successorParent->val == current->val) {
                successorParent->right = successor->right;
            } else {
                successorParent->left = successor->right;
            }
            successor->right = current->right;
            successor->left = current->left;
            current = successor;
        }

        if (currentParent == nullptr) {
            pRetVal = current;
            return pRetVal;
        }

        TreeNode* pFree = nullptr;
        if ((currentParent->left != nullptr) && (currentParent->left->val == key)) {
            pFree = currentParent->left;
            currentParent->left = current;
        } else {
            pFree = currentParent->right;
            currentParent->right = current;
        }
        delete pFree;
        pFree = nullptr;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> root;
        int key;
    };
    vector<subject> testData{{{5, 3, 6, 2, 4, imin, 7}, 3}, {{5, 3, 6, 2, 4, imin, 7}, 0}, {{}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [5,3,6,2,4,null,7], key = 3
     *  Output: [5,4,6,2,null,null,7]
     *
     *  Input: root = [5,3,6,2,4,null,7], key = 0
     *  Output: [5,3,6,2,4,null,7]
     *
     *  Input: root = [], key = 0
     *  Output: []
     */

    Solution cSolution;
    TreeNode* pRoot;
    TreeNode* pAnswer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: root = [";
        for (long unsigned int j = 0; j < testData[i].root.size(); ++j) {
            if (testData[i].root[j] == imin) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].root[j] == imax) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].root[j];
            }
        }
        cout << "], key = " << testData[i].key << "\n";
        pRoot = buildBinaryTree(testData[i].root, 0);

        pAnswer = cSolution.deleteNode(pRoot, testData[i].key);
        int height = getTreeHeight(pAnswer);
        cout << "Output: [";
        showTreeOutput(pAnswer, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pAnswer);
        pAnswer = nullptr;
        pRoot = nullptr;
    }

    return EXIT_SUCCESS;
}
