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
   private:
    pair<TreeNode*, int> dfs(TreeNode* root) {
        pair<TreeNode*, int> retVal = {nullptr, 0};

        if (root == nullptr) {
            return retVal;
        }

        pair<TreeNode*, int> left = dfs(root->left);
        pair<TreeNode*, int> right = dfs(root->right);
        if (left.second > right.second) {
            retVal = {left.first, left.second + 1};
        } else if (left.second < right.second) {
            retVal = {right.first, right.second + 1};
        } else {
            retVal = {root, left.second + 1};
        }

        return retVal;
    }

   public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        TreeNode* pRetVal = nullptr;

        pRetVal = dfs(root).first;

        return pRetVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> root;
        int target;
    };
    vector<subject> testData{{{3, 5, 1, 6, 2, 0, 8, imin, imin, 7, 4}}, {{1}}, {{0, 1, 3, imin, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [3,5,1,6,2,0,8,null,null,7,4]
     *  Output: [2,7,4]
     *
     *  Input: root = [1]
     *  Output: [1]
     *
     *  Input: root = [0,1,3,null,2]
     *  Output: [2]
     */

    Solution cSolution;
    TreeNode* pRoot = nullptr;
    TreeNode* pAnswer = nullptr;
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
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].root, 0);

        pAnswer = cSolution.lcaDeepestLeaves(pRoot);
        int height = getTreeHeight(pAnswer);
        cout << "Output: [";
        showTreeOutput(pAnswer, height);
        cout << "]\n";

        cout << "\n";

        freeTreeNode(pRoot);
        pRoot = nullptr;
        pAnswer = nullptr;
    }

    return EXIT_SUCCESS;
}
