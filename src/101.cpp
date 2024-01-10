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
    bool isMirror(TreeNode* left, TreeNode* right) {
        bool retVal = false;

        if ((left == nullptr) && (right == nullptr)) {
            retVal = true;
            return retVal;
        } else if ((left == nullptr) || (right == nullptr)) {
            return retVal;
        } else if (left->val != right->val) {
            return retVal;
        }
        retVal = (isMirror(left->left, right->right) && isMirror(left->right, right->left));

        return retVal;
    }
    bool isSymmetric(TreeNode* root) {
        bool retVal = true;

        if (root == nullptr) {
            return retVal;
        }
        retVal = isMirror(root->left, root->right);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> nums;
    };
    vector<subject> testData{{{1, 2, 2, 3, 4, 4, 3}},
                             {{1, 2, 2, numeric_limits<int>::min(), 3, numeric_limits<int>::min(), 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: root = [1,2,2,3,4,4,3]
     *  Output: true
     *
     *  Input: root = [1,2,2,null,3,null,3]
     *  Output: false
     */

    Solution cSolution;
    TreeNode* pRoot;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: root = [";
        for (long unsigned int j = 0; j < testData[i].nums.size(); ++j) {
            if (testData[i].nums[j] == numeric_limits<int>::min()) {
                cout << (j == 0 ? "" : ",") << "null";
            } else if (testData[i].nums[j] == numeric_limits<int>::max()) {
                continue;
            } else {
                cout << ((j == 0) ? "" : ",") << testData[i].nums[j];
            }
        }
        cout << "]\n";
        pRoot = buildBinaryTree(testData[i].nums, 0);

        answer = cSolution.isSymmetric(pRoot);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";

        freeTreeNode(pRoot);
    }

    return EXIT_SUCCESS;
}