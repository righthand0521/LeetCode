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
    TreeNode* searchBST(TreeNode* root, int val) {
        TreeNode* pRetVal = nullptr;

        if (root == nullptr) {
            return pRetVal;
        }

        if (root->val == val) {
            pRetVal = root;
        } else if (root->val > val) {
            pRetVal = searchBST(root->left, val);
        } else if (root->val < val) {
            pRetVal = searchBST(root->right, val);
        }

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> root;
        int val;
    };
    vector<subject> testData{{{4, 2, 7, 1, 3}, 2}, {{4, 2, 7, 1, 3}, 5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [4,2,7,1,3], val = 2
     *  Output: [2,1,3]
     *
     *  Input: root = [4,2,7,1,3], val = 5
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
        cout << "], val = " << testData[i].val << "\n";
        pRoot = buildBinaryTree(testData[i].root, 0);

        pAnswer = cSolution.searchBST(pRoot, testData[i].val);
        int height = getTreeHeight(pAnswer);
        cout << "Output: [";
        showTreeOutput(pAnswer, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
        pRoot = nullptr;
    }

    return EXIT_SUCCESS;
}
