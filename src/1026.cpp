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
    int dfs(TreeNode* root, int maxAncestor, int minAncestor) {
        int retVal = maxAncestor - minAncestor;

        if (root == nullptr) {
            return retVal;
        }

        maxAncestor = max(root->val, maxAncestor);
        minAncestor = min(root->val, minAncestor);
        int left = dfs(root->left, maxAncestor, minAncestor);
        int right = dfs(root->right, maxAncestor, minAncestor);
        retVal = max(left, right);

        return retVal;
    }
    int maxAncestorDiff(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }
        retVal = dfs(root, root->val, root->val);

        return retVal;
    }
};

int main(int argc, char** argv) {
    int imin = numeric_limits<int>::min();
    int imax = numeric_limits<int>::max();
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{8, 3, 10, 1, 6, imin, 14, imin, imin, 4, 7, imax, imax, 13}},
                             {{1, imin, 2, INT_MAX, INT_MAX, imin, 0, imax, imax, imax, imax, imax, imax, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
     *  Output: 7
     *
     *  Input: root = [1,null,2,null,0,3]
     *  Output: 3
     */

    Solution cSolution;
    TreeNode* pRoot;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: root = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            if (testData[i].nums[j] == imin) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].nums[j] == imax) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
            }
        }
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.maxAncestorDiff(pRoot);
        cout << "Output: " << answer << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}
